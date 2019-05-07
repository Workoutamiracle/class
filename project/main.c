#include <stdio.h>
#include <string.h>
#include <fcntl.h>
int main()
{

    int file;
    if((file = open("1.txt",O_RDONLY)) != -1){
        printf("incorrect password\n");
    }
    else {
        printf("Correct password\n");
    }
    int a;
    scanf("%d",&a);
    return 0;
}

