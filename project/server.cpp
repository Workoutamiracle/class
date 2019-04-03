#include <hiredis/hiredis.h>
#include <iostream>
#include <istream>
#include <string>
 
using namespace std;
 
int main()
{
    redisContext* c = redisConnect("127.0.0.1", 6379);
    if(c->err)
    {
        redisFree(c);
        cout << "Connect to redisServer fail" << endl;
        return 1;
    }

    string command;
    redisReply *r;
    cout << "127.0.0.1:6379 > ";
    while(r->type != REDIS_REPLY_ERROR) {
        getline(cin,command);
        r = (redisReply*)redisCommand(c, command.c_str());
            
        if(r->type == REDIS_REPLY_STRING)   //返回值为字符串
            cout << r->str << endl;
        else if(r->type == REDIS_REPLY_INTEGER) //返回值为整数
            cout << "(integer) " << r->integer << endl;
        else if(r->type == REDIS_REPLY_ARRAY) {//返回值为数组
            for(size_t i = 0;i < r->elements;++i)          
                cout << i+1 << ") " << (r->elements)[i]->str << endl;
        
        }

        if(!command.compare("quit"))
            break;
        cout << "127.0.0.1:6379 > ";
    }
    return 0;
}

