#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
int main()
{

    int file;
    if((file = open("./1.txt",O_RDONLY) != -1)){
        printf("incorrect password\n");
    }
    else {
        printf("Correct password\n");
    }
    printf("main file=%d\n",file);
    close(file);
    return 0;
}

