#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>

void func(const char *s1,int flags,...)
{
    va_list va;
    va_start(va,flags);
    mode_t tmp = va_arg(va,int);
    printf("%d\n",tmp);
}
void get_file_name (const int fd,char *path)
{

  char buf[1024] = {'\0'};
  snprintf(buf, sizeof (buf), "/proc/self/fd/%d", fd);
  readlink(buf, path, 100);
}

int main()
{
    int fd = open("./1.txt",O_RDONLY);
    printf("%d\n",fd);
    char path[100];

    get_file_name(fd,path);
    printf("%zd\n",strlen(path));
    path[strlen(path)-2] = '\0';
    printf("%s\n",path);
    close(fd);
    return 0;
}

