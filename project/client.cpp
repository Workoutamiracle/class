#include <iostream>
#include <thread>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


#define FILEPATH "/etc/passwd"
#define PROJID 1234
struct Buf{
    long mtype;
    char mtext[BUFSIZ];
};

void handle(int msgid,long type,char *file_buf)
{
    Buf buf;
    buf.mtype = type;
    std::cout << "文件路径:" << file_buf << std::endl;
    std::cout << "进程id:" << type << std::endl;
    std::cin >> buf.mtext;

    while(msgsnd(msgid,&buf,sizeof(buf)-sizeof(long),0) != -1) {
        std::cin >> buf.mtext; 
    }
}
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
    msgid = msgget(key, IPC_CREAT|IPC_EXCL|0600);
    if (msgid == -1) {
        perror("msgget()");
        exit(1);
    }

    Buf buf;

    //等待hook程序发送文件路径以及进程id
    while(msgrcv(msgid,&buf,sizeof(buf) - sizeof(long),0,0) != -1) {
        //创建线程处理来自此hook程序的请求
        std::thread t(handle,msgid,buf.mtype,buf.mtext);
        t.detach();
    }

    return 0;
}

