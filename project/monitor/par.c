#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int main()
{
    const char *file_name = "./hook.c";
     char abs_path_buff[PATH_MAX];

     //获取文件路径, 填充到abs_path_buff
     //realpath函数返回: null表示获取失败; 否则返回指向abs_path_buff的指针
     if(realpath(file_name, abs_path_buff)){
         printf("%s %s\n", file_name, abs_path_buff);
     }
     else{
         printf("the file '%s' is not exist\n", file_name);
     }

    char s1[100];
    char s2[100];
    while(1) {
        scanf("%s",s1);
        scanf("%s",s2);
        int i = strcmp(s1,s2);
        if(i == 0) {
            printf("相等\n");
        }else if(i > 0)
            printf("大于\n");
        else
            printf("小于\n");
        bzero(s1,100);
        bzero(s2,100);

    }
    return 0;
}

