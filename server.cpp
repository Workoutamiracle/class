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

using namespace std;

int fd;
void *thread_hand(int fd)
{
    char ch;
    while(recv(fd,&ch,1,0) > 0) {
        cout << ch << endl;
        send(fd,&ch,1,0);
    }
    
}
void signalhandler(int sig)
{
    
    pid_t pid;
    if((pid = fork()) == 0) {
        const char *ar = to_string(fd).c_str();
        
        cout << "子进程准备执行" << endl;
        //执行新的server文件
        if(execl("/home/wh/class/server","./server",ar,NULL) < 0) {
            cout << "子进程开始执行" << endl;
        } 
    }else if(pid > 0) {
        wait(NULL);
    }
}
void handle(int sig)
{
    cout << "关闭子进程" << endl;
    exit(0);
}
void handle2(int sig)
{
    cout << "关闭父进程" << endl;
    kill(getppid(),SIGINT);
}
int main(int argc,char *argv[])
{
    
    if(argc == 1) {
        signal(SIGTSTP,signalhandler);
        fd = socket(AF_INET,SOCK_STREAM,0);
        if(fd < 0) {
            cout << "套接字申请失败" << endl;
            exit(0);
        }

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
            cout << sockfd << endl;
            thread t(thread_hand,sockfd);        
            t.detach();
            /*
            cin >> flag;
            if(flag == 1) {
                pid_t pid;
                if((pid = fork()) == 0) {
                    const char *ar = to_string(fd).c_str();
                    cout << "子进程准备执行" << endl;
                    //执行新的server文件
                    if(execl("/home/wh/class/server","./server",ar,NULL) < 0) {
                        cout << "子进程开始执行" << endl;
                    } 
                }else if(pid > 0) {
                    wait(&flag); 
                }

            }
            */
        }
    }
    else {
        signal(SIGINT,handle);
        signal(SIGQUIT,handle2);
        cout << "子进程开始执行" << endl;
        int fd = argv[1][0] - '0';
        int sockfd;
        while((sockfd = accept(fd,NULL,NULL)) > 0) {
            thread t(thread_hand,sockfd);        
            t.detach();
        }
    }
    return 0;

}
