#include <hiredis/hiredis.h>
#include <iostream>
 
using namespace std;
 
int main()
{
    redisContext* c = redisConnect("127.0.0.1", 6379);
    redisReply *reply;
    if ( c->err)
    {
        redisFree(c);
        cout << "Connect to redisServer fail" << endl;
        return 1;
    }
    cout << "Connect to redisServer Success" << endl;
    redisReply* r = (redisReply*)redisCommand(c, "set ccc ccc");
    cout << r->str << endl;
    r = (redisReply*)redisCommand(c, "get ccc");
    cout << r->str << endl;
    return 0;
}

