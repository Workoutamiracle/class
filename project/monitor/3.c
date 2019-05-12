#include <stdio.h>

void func(size_t n,int a[][n]) {
    a[0][0] = 1;
}


int main()
{
    int a[][2] = {2,0,1,9};
    func(sizeof(a),a);
    printf("%d\n",a[0][0]);
    return 0;
}

