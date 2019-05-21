#include <iostream>
#include <stdlib.h>
#include "Thread_Download.h"

//解析url链接
void HTTP::Parse() {
    string::size_type pos; 
    //解析域名
    pos = url.find("//");
    url = url.substr(pos+2,url.length()-pos-2);
    pos = url.find("/");
    host = url.substr(0,pos);

    //解析端口号
    pos = url.find(":");
    if(pos != string::npos) {
        port = url.substr(pos+1,url.find_first_not_of("0123456789",pos+1));
        //删除域名内的端口号
        pos = host.find_first_of(":",0);
        host = host.substr(0,pos);
    }
   //解析ip地址
    auto h = gethostbyname(host.c_str()); 
    if(h->h_addr_list[0])
        ip_addr = inet_ntoa(*((struct in_addr *)h->h_addr_list[0]));

    struct addrinfo hints,*res;
    bzero(&hints,sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = 0;
    int n;
    
    if( (n = (getaddrinfo(host.c_str(),NULL,&hints,&res))) != 0 ) {
        std::cout << "getaddrinfo error" << std::endl;
    }
    for(auto p = res;p;p = p->ai_next) {
        std::cout << inet_ntoa(((struct sockaddr_in *)p->ai_addr)->sin_addr) << std::endl;
        std::cout << ntohs(((struct sockaddr_in *)p->ai_addr)->sin_port) << std::endl;
    }

    freeaddrinfo(res);

    std::cout << url << std::endl;
    std::cout << port << std::endl;
    std::cout << host << std::endl;
    std::cout << ip_addr << std::endl;
    std::cout << h->h_name << std::endl;

}

//设置http请求头并发送
void HTTP::SendHttpHead(long start,long end) {
    string head = "GET "+url+" HTTP/1.1\r\n"+
            "Accept: */*\r\n"+
            "Host: "+host+"\r\n"+
            "Connection: keep-alive\r\n"+
            "Range: bytes="+to_string(start)+"-"+((end>0)?to_string(end):"")+"\r\n"+
            "\r\n";
        
}

//接收http响应头并解析


//与远程服务器建立连接
int HTTP::Connect() {
    int fd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(fd < 0) {
        std::cout << "套接字创建失败" << std::endl;
        exit(0);
    }

    struct sockaddr_in addr;
    memset(&addr,0,sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip_addr.c_str());
    addr.sin_port = htons(atoi(port.c_str()));

    int res = connect(fd,(struct sockaddr *)&addr,sizeof(addr));
        if(res == -1) {
            cout << "连接失败" << endl;
            return 0;
        }
        return 1;
}


