#include <stdio.h>
struct A{
    long a;
    int b;
};
int main()
{
    struct A num = {0x6e694c756f796978,0x7875};
    char ch = '0';
    for(int i = 0;ch;++i)
    {
        ch = *((char *)&num + i);
        printf("%c",ch);
    }
    return 0;
}

