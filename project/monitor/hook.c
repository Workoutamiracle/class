#include <stdio.h>
#include <string.h>
#include <dlfcn.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>
#include <stdarg.h>
#include <fcntl.h>

#define FILEPATH "/home"
#define PROJID 1234

#define OPEN 1  //open请求
#define CLOSE 2 //close请求
#define FINISH 3//文件修改完成应答
#define ALIVE 4 //客户端与服务器连接断开应答
#define INVALID 5//文件非监控目录应答
#define ACCESS 6//返回文件是否存在应答

//函数参数
struct Parameter{
    char Path[100]; //文件路径
    int flag;      //打开标志
    mode_t mode;    //若第二个参数存在O_CREAT且文件不存在，则为新文件的权限
};

//消息类型
struct data{
    long type;
    pid_t pid;
    struct Parameter mtext;
};

//消息队列结构体类型
struct Buf {
    long mtype;
    struct data mdata;
};

//消息内容
struct Packet{
    //消息请求类型
    int type;
    //客户端id
    pid_t pid;
    //对文件的操作
    int flag;
    //操作权限
    mode_t mode;
    //文件路径
    char pathName[PATH_MAX];

};
//消息对垒格式的包
struct Msg{
    //消息类型
    long type;
    //消息数据
    struct Packet buf;
};

//得到队列标识符
int GetKey()
{
    int msgid;
    key_t key;

    key = ftok(FILEPATH, PROJID);
    if (key == -1) {
        perror("ftok()");
        exit(1);
    }

    msgid = msgget(key, 0);
    if (msgid == -1) {
        perror("msgget()");
        exit(1);
    }
    return msgid;
}

//根据文件描述符获取文件绝对路径
void get_file_name (const int fd,char *path)
{

    printf("%d\n",fd);
    char buf[1024] = {'\0'};
    snprintf(buf, sizeof (buf), "/proc/self/fd/%d", fd);
    readlink(buf, path, 100);
}

typedef int(*Open)(const char *pathname,int flags,...);
//typedef int(*Open2)(const char *s1,int flags,mode_t mode);

int open(const char *s1,int flags,...)
{       
    mode_t tmp = 0;
    if(flags & O_CREAT) {
        //获取第三个参数
        va_list va;
        va_start(va,flags);
        tmp = va_arg(va,int); 
        va_end(va);
        printf("%d\n",tmp);
    }


    struct Buf buf;
    struct Msg msg;
    //根据文件相对路径获取绝对路径
    realpath(s1,buf.mdata.mtext.Path); 
    buf.mdata.mtext.flag = flags;
    buf.mdata.mtext.mode = tmp;

    realpath(s1,msg.buf.pathName);
    msg.buf.flag = flags;
    msg.buf.mode = tmp;

    int msgid = GetKey();
    printf("msgid = %d\n",msgid);

    //发送OPEN请求到消息队列
    buf.mtype = 1;
    buf.mdata.pid = getpid();
    buf.mdata.type = OPEN;
    
    msg.type = 1;
    msg.buf.pid = getpid();
    msg.buf.type = OPEN;

    printf("旧数据:%s %d %u\n",buf.mdata.mtext.Path,buf.mdata.mtext.flag,buf.mdata.mtext.mode);
    printf("新数据:%s %d %u\n",msg.buf.pathName,msg.buf.flag,msg.buf.mode);


    if (msgsnd(msgid, (void *)&msg, sizeof(msg) - sizeof(long), 0) < 0) {
        perror("msgsnd()");
        printf("%d",errno);
        exit(1);
    }



    //已将open请求发送给客户端,等待客户端返回通知
    struct Buf Recv_buf;
    struct Msg Recv_msg;

    while(1) {
        int i = 0;
        if((i = msgrcv(msgid,&Recv_msg,sizeof(Recv_msg) - sizeof(long),getpid(),0)) > 0) {
            switch(Recv_msg.buf.type) {
            case ALIVE:
                printf("alive\n");
                //服务器与客户端连接已断开，拒绝任何程序打开监控目录下的所有文件
                return -1;
            case INVALID:
                printf("invalid\n");
                //文件非监控目录下,直接返回其描述符
                break;
            case FINISH:
                printf("finish\n");
                //服务器已备份完文件内容，可返回文件描述符
                break; 
            case ACCESS:
                printf("access\n");
                return -1;
            }
        }
        if(i)
            break;
    }
    
    static void *handle = NULL;
    static Open old_open = NULL;

    if(!handle) {
        handle = dlopen("libc.so.6",RTLD_LAZY);
        old_open = (Open)dlsym(handle,"open");
    }

    if(tmp) {
        printf("open2\n");
        return old_open(s1,flags,tmp);
    }
    else {
        printf("open\n");
        return old_open(s1,flags);   
    }
}

typedef int(*Close)(int fd);

int close(int fd)
{
    int msgid = GetKey();
    struct Buf buf;
    struct Msg msg;

    //发送CLOSE请求到客户端
    buf.mtype = getpid();
    buf.mdata.type = CLOSE;

    msg.type = getpid();
    msg.buf.type = CLOSE;

    memset(buf.mdata.mtext.Path,0,100);
    memset(msg.buf.pathName,0,100);

    get_file_name(fd,buf.mdata.mtext.Path);
    get_file_name(fd,msg.buf.pathName);

    printf("旧数据Path=%s mtype=%ld\n",buf.mdata.mtext.Path,buf.mtype);
    printf("新数据Path=%s mtype=%ld\n",msg.buf.pathName,msg.type);

    if (msgsnd(msgid, &msg, sizeof(msg) - sizeof(long), 0) == -1) {
        perror("msgsnd()");
        exit(1);
    }

     //已将close请求发送给客户端,等待客户端返回通知
    struct Buf Recv_buf;
    struct Msg Recv_msg;

    if(msgrcv(msgid,&Recv_msg,sizeof(Recv_msg) - sizeof(long),getpid(),0) != -1) {
        switch(Recv_msg.buf.type) {
            case ALIVE:
                //服务器与客户端连接已断开，拒绝任何程序关闭监控目录下的所有文件
                return -1;
            case FINISH:
                //服务器已恢复完文件内容，可正常返回
                break;
            case ACCESS:
                //文件非监控目录，正常返回
                break;
        }
    }
    
    static void *handle = NULL;
    static Close old_close = NULL;

    if(!handle) {
        handle = dlopen("libc.so.6",RTLD_LAZY);
        old_close = (Close)dlsym(handle,"close");
    }
    return old_close(fd);
}
