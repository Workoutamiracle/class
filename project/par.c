#include <stdio.h>
struct A{
    int a;
    long b;
    char ch[50];
};
int main()
{
    char ch;
    int num;

    ch = 1;
    num = 2;

    printf("%zd\n",sizeof(struct A));
    return 0;
}

