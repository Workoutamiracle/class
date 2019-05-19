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
    char *c = &ch;
    int *p = &num;

    printf("c=%p\n",c);
    printf("c+1=%p\n",c+1);
    printf("p=%p\n",p);
    printf("p+1=%p\n",p+1);

    printf("%zd\n",sizeof(struct A));
    return 0;
}

