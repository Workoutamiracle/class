#include <iostream>
#include <vector>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <wait.h>
#include <thread>
#include <csignal>
#include <fstream>
#include <mutex>

using namespace std;

int fd;
mutex g_lock;
void handle(int sockfd)
{
    int size;
    char ch;
    while((size = recv(sockfd,&ch,1,0)) > 0) {
        send(sockfd,&ch,1,0);
    }
}
void manage(int sig);

int main(int argc,char *argv[])
{
    
    if(argc == 1) {
        fd = socket(AF_INET,SOCK_STREAM,0);
        if(fd < 0) {
            cout << "套接字申请失败" << endl;
            exit(0);
        }
        signal(SIGTSTP,manage);

        struct sockaddr_in serv;
        memset(&serv,0,sizeof(serv));
        serv.sin_family = AF_INET;
        serv.sin_port = htons(5678);
        serv.sin_addr.s_addr = htonl(INADDR_ANY);

        int num = 1;
        int length = sizeof(num);
	    setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,&num,length);
        
        if(bind(fd,(struct sockaddr *)&serv,sizeof(serv)) < 0) {
            cout << "绑定失败 " << endl;
            exit(0);
        }

        if(listen(fd,5) < 0) {
            cout << "创建监听套接字失败" << endl;
            exit(0);
        }

        int sockfd;
        while((sockfd = accept(fd,NULL,NULL)) > 0) {
            cout << "主线程" << endl;
            thread t(handle,sockfd);
            t.detach();
            g_lock.lock();
            g_lock.unlock();
        }
    }
    else {
        cout << "线程2开始执行" << endl;        
        int sockfd;
        
        cout << fd << endl;
        while((sockfd = accept(fd,NULL,NULL)) > 0) {
            g_lock.lock();
            cout << "线程2" << endl;
            thread t(handle,sockfd);
            t.detach();

        }
        g_lock.unlock();
    }
    return 0;

}
void manage(int sig)
{
    char **ar;
    thread t(main,2,ar);
    t.detach();
}



