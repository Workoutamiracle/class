#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
int main()
{
    int fd;
    if((fd = open("./1.txt",O_RDONLY|O_WRONLY))!= -1){
        printf("incorrect password\n");
    }
    else {
        printf("Correct password\n");
    }
    char c;
    scanf("%c",&c);
    close(fd);
    return 0;

}

