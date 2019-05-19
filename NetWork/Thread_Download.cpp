#include <iostream>
#include "Thread_Download.h"

//解析url链接
void HTTP::Parse()
{
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

    std::cout << url << std::endl;
    std::cout << port << std::endl;
    std::cout << host << std::endl;
    std::cout << ip_addr << std::endl;
}
void HTTP::SendHttpHead(long start,long end)
{
    string head = "GET "+url+" HTTP/1.1\r\n"+
            "Accept: */*\r\n"+
            "Host: "+host+"\r\n"+
            "Connection: keep-alive\r\n"+
            "Range: bytes="+to_string(start)+"-"+((end>0)?to_string(end):"")+"\r\n"+
            "\r\n";
        
}

