#include <stdio.h>
#include <string.h>
#include <dlfcn.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

#define FILEPATH "/etc/passwd"
#define PROJID 1234
#define MSG "hello world!"

#define OPEN 1  //open请求
#define CLOSE 2 //close请求
#define FINISH 3//文件修改完成应答
#define ALIVE 4 //客户端与服务器连接断开应答
#define INVALID 5//文件非监控目录应答

struct data{
    long type;
    char mtext[BUFSIZ];
};

struct Buf {
    long mtype;
    struct data mdata;
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

  char buf[1024] = {'\0'};
  snprintf(buf, sizeof (buf), "/proc/self/fd/%d", fd);
  readlink(buf, path, sizeof(path) - 1);
}

typedef int(*Open)(const char *s1,int mode);

int open(const char *s1,int mode)
{    
    struct Buf buf;
    //根据文件相对路径获取绝对路径
    realpath(s1,buf.mdata.mtext); 
    
    int msgid = GetKey();

    //发送OPEN请求到消息队列
    buf.mtype = getpid();
    buf.mdata.type = OPEN;

    if (msgsnd(msgid, &buf, sizeof(buf) - sizeof(long), 0) == -1) {
        perror("msgsnd()");
        exit(1);
    }

    //已将open请求发送给客户端,等待客户端返回通知
    struct Buf Recv_buf;

    if(msgrcv(msgid,&Recv_buf,sizeof(Recv_buf) - sizeof(long),getpid(),0) != -1) {
        switch(Recv_buf.mdata.type) {
            case ALIVE:
                //服务器与客户端连接已断开，拒绝任何程序打开监控目录下的所有文件
                return -1;
            case INVALID:
                //文件非监控目录下,直接返回其描述符
                break;
            case FINISH:
                //服务器已备份完文件内容，可返回文件描述符
                break; 
        }
    }
    
    static void *handle = NULL;
    static Open old_open = NULL;

    if(!handle) {
        handle = dlopen("libc.so.6",RTLD_LAZY);
        old_open = (Open)dlsym(handle,"open");
    }
    return old_open(s1,mode);
}

typedef int(*Close)(int fd);

int close(int fd)
{
    int msgid = GetKey();
    struct Buf buf;
    //发送CLOSE请求到客户端
    buf.mtype = getpid();
    buf.mdata.type = CLOSE;
    get_file_name(fd,buf.mdata.mtext);

    if (msgsnd(msgid, &buf, sizeof(buf) - sizeof(long), 0) == -1) {
        perror("msgsnd()");
        exit(1);
    }

     //已将close请求发送给客户端,等待客户端返回通知
    struct Buf Recv_buf;

    if(msgrcv(msgid,&Recv_buf,sizeof(Recv_buf) - sizeof(long),getpid(),0) != -1) {
        switch(Recv_buf.mdata.type) {
            case ALIVE:
                //服务器与客户端连接已断开，拒绝任何程序打开监控目录下的所有文件
                return -1;
            case FINISH:
                //服务器已恢复完文件内容，可正常返回
                break;
        }
    }
    
    static void *handle = NULL;
    static Close old_close = NULL;

    if(!handle) {
        handle = dlopen("libc.so.6",RTLD_LAZY);
        old_close = (Close)dlsym(handle,"open");
    }
    return old_close(fd);
   
}
