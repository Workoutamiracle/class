#include <stdio.h>
#include <string.h>
#include <dlfcn.h>

typedef int(*OPEN)(const char *s1,int mode);

int open(const char *s1,int mode)
{
    static void *handle = NULL;
    static OPEN old_open = NULL;

    if(!handle) {
        handle = dlopen("libc.so.6",RTLD_LAZY);
        old_open = (OPEN)dlsym(handle,"open");
    }
    printf("oops!!!hack function invoked,s = %s mode = %d\n",s1,mode);
    return old_open(s1,mode);
}

