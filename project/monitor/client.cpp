#include <iostream>
#include <fstream>
#include <istream>
#include <thread>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


#define FILEPATH "/home"
#define PROJID 1234

#define OPEN 1  //open请求
#define CLOSE 2 //close请求
#define FINISH 3//文件修改完成应答
#define ALIVE 4 //客户端与服务器连接断开应答
#define INVALID 5//文件非监控目录应答

struct data{
    long type;
    char mtext[BUFSIZ-8];
};

struct Buf {
    long mtype;
    struct data mdata;
};

int alive = 1;
void Send_handle(int msgid,Buf buf)
{
    Buf Recv_buf;
    Recv_buf.mtype = buf.mdata.type;

    //检测文件所在目录是否为被监控目录
    if(strncmp(FILEPATH,buf.mdata.mtext,strlen(FILEPATH))) {
        //非被监控目录
        Recv_buf.mdata.type = INVALID;
        if(msgsnd(msgid,&Recv_buf,sizeof(Buf) - sizeof(long),0) == -1) {
            perror("msgsnd");
            exit(1);
        }
        return;
        
    }
    
    //检测全局变量确定与服务器连接是否断开
    if(!alive) {
        //与服务器连接已断开，向消息队列发送ALIVE应答
       Recv_buf.mdata.type = ALIVE;
        if(msgsnd(msgid,&Recv_buf,sizeof(Buf) - sizeof(long),0) == -1) {
            perror("msgsnd");
            exit(1);
        }
        return;
    }

    //打开文件,改变其内容
    
    std::fstream file(buf.mdata.mtext,std::ios::out);

    std::string new_file = "1234567";
    file << new_file;
    file.close();

    std::cout << "修改完成,发送通知" << std::endl;

    //发送修改完成通知给hook程序
    Recv_buf.mdata.type = FINISH;
    if(msgsnd(msgid,&Recv_buf,sizeof(Buf) - sizeof(long),0) == -1) {
            perror("msgsnd");
            exit(1);
    }


    //将文件内容发送给服务器
 //   SendData();

    //备份完成等待hook程序发送close请求
    if(msgrcv(msgid,&buf,sizeof(buf) - sizeof(long),buf.mtype,0) != -1) {
        //同一进程未调用close之前又调用open打开相同文件
        switch(buf.mtype) {
        case OPEN:
            //...
            break;
   //     case CLOSE:
            //向服务器发送close请求
  //          SendData();
            
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
    //创建线程处理来自服务器的应答
    

    //等待hook程序发送文件路径以及进程id
    while(msgrcv(msgid,&buf,sizeof(buf) - sizeof(long),2,0) != -1) {
        //创建线程处理来自此hook程序的请求
        std::thread t(Send_handle,msgid,buf);
        t.detach();
    }

    return 0;
}

