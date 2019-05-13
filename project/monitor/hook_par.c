#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <dlfcn.h>
#include <fcntl.h>
/*
   hook的目标是strcmp，所以typedef了一个STRCMP函数指针
   hook的目的是要控制函数行为，从原库libc.so.6中拿到strcmp指针，保存成old_strcmp以备调用
   */
typedef int(*OPEN)(const char *pathname, int flags,...);

int open(const char *pathname, int flags,...)
{
    static void *handle = NULL;
    static OPEN old_open = NULL;

    if( !handle )
    {
        handle = dlopen("libc.so.6", RTLD_LAZY);
        old_open = (OPEN)dlsym(handle, "strcmp");
    }
    return old_open(pathname, flags);
}

