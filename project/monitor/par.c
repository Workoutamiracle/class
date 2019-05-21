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
void get_file_name (const int fd,int n,char path[n])
{

  char buf[1024] = {'\0'};
  snprintf(buf, sizeof (buf), "/proc/self/fd/%d", fd);
  readlink(buf, path, n);
}

int main()
{
    int fd = open("./1.txt",O_RDONLY);
    printf("%d\n",fd);
    char path[100];
    memset(path,0,sizeof(path));


    get_file_name(fd,sizeof(path),path);
    printf("%zd\n%s\n",strlen(path),path);
    close(fd);

    int fd_new = open("./3.jpeg.tar.gz",O_RDONLY);
    char ch[100];

    int fd_create = open("./4.jpeg",O_WRONLY | O_CREAT,0777);

    int i = 0,j = 0;
    
    while((i += read(fd_new,ch,100)) == 100) {
        while((j += write(fd_create,ch,100)) == 100) {
            j = 0;
            break;
        }
        i = 0;
    }
    close(fd_new);
    close(fd_create);

    return 0;
}

