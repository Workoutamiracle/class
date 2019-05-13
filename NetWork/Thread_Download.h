#ifndef DD
#define DD
#include <iostream>
#include <string>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <fstream>
#include <pthread.h>
#include <vector>
#include <sys/stat.h>
#include <cstdio>
#include <iomanip>
#include <thread>


using namespace std;
//下载任务类
class Download{
public:
    Download(string &_url) : url(_url) {  }
    Download(string &_url,string &_path) : url(_url),Path(_path) {  }
    Download(string &_url,string &_path,string &_name) : url(_url),Path(_path),name(_name) {  }
    ~Download() = default;
private:
    //通过url解析出需下载的文件大小和类型
    void GetAttribute();
    //多线程下入文件内容
    void Write_Thread();
    //合并每个线程单独写的文件
    void Mergefile(int num);

    string url;         //下载链接
    string Path = ".";    //文件保存路径
    string name;    //文件保存名
    long size;      //文件大小
    string type;    //文件类型;
};

//http操作类
class HTTP{
public:
    HTTP(string &_url) : url(_url) { Parse(); }
    //发送http请求头
    void SendHttpHead(long start,long end);
     //读取http响应头
    void ReadHttpHead();
    //解析http响应头
    void ParseHead();
private:
    //解析url链接
    void Parse();
    //与远程服务器建立连接
    int COnnect();

    string url; //下载链接
    string port = "80";   //服务器端口号
    string host;//远程主机地址
    string ip_addr;//主机ip地址
};
#endif
