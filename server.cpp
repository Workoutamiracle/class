#include <iostream>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

using namespace std;

int main(int argc,char *argv[])
{
    
    if(argc == 1) {
        int fd = socket(AF_INET,SOCK_STREAM,0);
        if(fd < 0) {
            cout << "套接字申请失败" << endl;
            exit(0);
        }

        struct sockaddr_in serv;
        memset(&serv,0,sizeof(serv));
        serv.sin_family = AF_INET;
        serv.sin_port = htons(6379);
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

        int sockfd = accept(fd,NULL,NULL);
        char ch = 'H';
        send(sockfd,&ch,1,0);

        pid_t pid;
        const char *ar = to_string(sockfd).c_str();
        int flag;
        cin >> flag;
        //接收到信号后重新执行server可执行文件
        if(flag == 1) {
            pid = fork();
            if(pid == 0) { //子进程
                cout << "子进程准备执行" << endl;
                //执行新的server文件
                if(execl("/home/wh/class/server","./server",ar,NULL) < 0) {
                    cout << "子进程开始执行" << endl;
                } 
            }
            else if(pid > 0) {
                //等待子进程与客户端连接完成
                cout << "父进程等待子进程执行" << endl;
                recv(sockfd,&ch,1,0);
                if(ch == 'a') {
                    cout << "子进程执行,结束父进程" << endl;
                    exit(0);

                }
            }
            close(fd);
        }
    }
    else {
        cout << "子进程开始执行" << endl;
        int fd = argv[1][0] - '0';
        char ch = 'a';
        send(fd,&ch,1,0);
       
        for(int i = 0;i < 10;++i) {
            sleep(1);
            ch = 'c';
            send(fd,&ch,1,0);
        }
}

    return 0;
}
