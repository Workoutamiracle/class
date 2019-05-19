#include <iostream>
#include <fstream>
#include <istream>
#include <thread>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>


#define FILEPATH "/home"
#define PROJID 1234

#define OPEN 1  //open请求
#define CLOSE 2 //close请求
#define FINISH 3//文件修改完成应答
#define ALIVE 4 //客户端与服务器连接断开应答
#define INVALID 5//文件非监控目录应答
#define ACCESS 6 //返回文件不存在应答

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
    Packet buf;
};


int alive = 1;
std::string word;
void Send_handle(int msgid,Msg msg)
{
    Buf buf;
    Buf Recv_buf;
    Msg Recv_msg;
    //将消息类型按进程id区分
    Recv_buf.mtype = buf.mdata.pid;
    std::cout << "旧数据="<<buf.mdata.mtext.flag << std::endl;
    std::cout << "旧数据="<<buf.mdata.mtext.mode << std::endl;

    Recv_msg.type = msg.buf.pid;
    std::cout << "新数据="<<msg.buf.flag << std::endl;
    std::cout << "新数据="<<msg.buf.mode << std::endl;

    //检测文件是否存在且函数参数是否含有O_CREAT
    if(access(msg.buf.pathName,F_OK) == -1) {
        //文件不存在且含有O_CREAT
        if(msg.buf.flag & O_CREAT) {
            std::cout << "文件不存在,创建文件" << std::endl;
            std::cout << buf.mdata.mtext.flag << std::endl;
            std::cout << buf.mdata.mtext.mode << std::endl;
            //创建文件
            if(open(msg.buf.pathName,msg.buf.flag,msg.buf.mode) == -1) {
                perror("create");
                exit(0);
            }
        }
        else {
            std::cout << "文件不存在,不能创建文件" << std::endl;
            Recv_msg.buf.type = ACCESS;
            if(msgsnd(msgid,&Recv_msg,sizeof(Msg) - sizeof(long),0) == -1) {
                perror("msgsnd");
                exit(1);
            }
            return;
        }
    }

    //检测文件所在目录是否为被监控目录
    if(strncmp(FILEPATH,msg.buf.pathName,strlen(FILEPATH))) {
        //非被监控目录
        Recv_msg.buf.type = INVALID;
        if(msgsnd(msgid,&Recv_msg,sizeof(Msg) - sizeof(long),0) == -1) {
            perror("msgsnd");
            exit(1);
        }
        return;
        
    }
    
    //检测全局变量确定与服务器连接是否断开
    if(!alive) {
        //与服务器连接已断开，向消息队列发送ALIVE应答
       Recv_msg.buf.type = ALIVE;
        if(msgsnd(msgid,&Recv_msg,sizeof(Msg) - sizeof(long),0) == -1) {
            perror("msgsnd");
            exit(1);
        }
        return;
    }
    //打开文件，将其内容保存下来
    std::fstream file(msg.buf.pathName,std::ios::in);
    file >> word;
    file.close();

    //打开文件,改变其内容
    file.open(msg.buf.pathName,std::ios::out);
    std::string new_file = "1234567";
    file << new_file;
    file.close();

    std::cout << "修改完成,发送通知" << std::endl;

    //发送修改完成通知给hook程序
    Recv_msg.buf.type = FINISH;
    if(msgsnd(msgid,&Recv_msg,sizeof(Msg) - sizeof(long),0) == -1) {
            perror("msgsnd");
            exit(1);
    }


    //将文件内容发送给服务器
 //   SendData();

    //备份完成等待hook程序发送close请求
    if(msgrcv(msgid,&msg,sizeof(msg) - sizeof(long),msg.buf.pid,0) != -1) {
        std::cout << "收到close请求" << std::endl;
        //检测文件所在目录是否为被监控目录
        if(strncmp(FILEPATH,msg.buf.pathName,strlen(FILEPATH))) {
            //非被监控目录
            Recv_msg.buf.type = ACCESS;
            if(msgsnd(msgid,&Recv_msg,sizeof(Msg) - sizeof(long),0) == -1) {
                perror("msgsnd");
                exit(1);
            }
            return;
        }
        
        //同一进程未调用close之前又调用open打开相同文件
        switch(msg.buf.type) {
        case OPEN:
            //...
            break;
        case CLOSE:
            //向服务器发送close请求
            //SendData();
            //修改文件内容
            std::cout << "源文件内容为:" << word << std::endl;
            file.open(msg.buf.pathName,std::ios::out);
            file << word;
            file.close();
            //修改完成返回FINISH
            Recv_msg.buf.type = FINISH;
            if(msgsnd(msgid,&Recv_msg,sizeof(Msg) - sizeof(long),0) == -1) {
                perror("msgsnd");
                exit(1);
            }
            
            break;
        }
    } 
}

/*
//从服务器接收数据并处理
void Recv_handle(int msgid,struct Buf buf,int fd)
{
      
    while((Data = RecvData()) > 0) {
        switch(Data) {
        case FINISH:
            //接收到文件新/旧内容，将文件内容替换
            file_replace(buf.mdata.mtext,Data.mtext);
            //备份/还原文件内容完毕,向消息队列添加FINISH应答
            struct Buf Recv_buf;
            Recv_buf.mtype = buf.mtype;
            Recv_buf.mdata.type = FINISH;
            if(msgsnd(msgid,&Recv_buf,sizeof(Buf) - sizeof(long),0) == -1) {
                perror("msgsnd");
                exit(1);
            }
            break; 
         
        }
    }
}

*/
int main()
{
    int msgid;
    key_t key;

    key = ftok(FILEPATH, PROJID);
    if (key == -1) {
        perror("ftok()");
        exit(1);
    }
    
    //创建消息队列
    msgid = msgget(key, IPC_CREAT|0600);
    if (msgid == -1) {
        perror("msgget()");
        exit(1);
    }

    Buf buf;
    Msg msg;
    //创建线程处理来自服务器的应答
    

    //等待hook程序发送文件路径以及进程id
    while(msgrcv(msgid,&msg,sizeof(msg) - sizeof(long),1,0) != -1) {
        //创建线程处理来自此hook程序的请求
        std::thread t(Send_handle,msgid,msg);
        t.detach();
    }

    return 0;
}

