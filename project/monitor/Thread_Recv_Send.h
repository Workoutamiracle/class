#pragma once
#include <iostream>
struct AttriBute{
    long l_range;
    long r_range;
    char  buf;
};

class Thread_Recv_Send {
public:
    //构造函数
    Thread_Recv_Send(const int &_fd,const std::string &_file,const int &_tnum) : fd(_fd),file_path(_file),thread_num(_tnum) {  } 
    //析构函数
    ~Thread_Recv_Send()=default;

        

private:
    int fd;                 //使用的套接字
    std::string file_path;  //文件路径
    int thread_num;         //线程数量
};

