#include <stdio.h>
#include <string.h>
struct node{
    char a;
    int b;
    short c;
};

struct n{
    char a;
    int b;
};

int main()
{
    struct node a[2] = {{1,2,3},{4,5,6}};
    *(int *)((char *)a+2*sizeof(struct n)) = 100;
    return 0;
}

