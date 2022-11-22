#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
int foo(int);
int main()
{
    // //指针和指针函数
    // int a = 10;
    // // int *p = a;
    // // printf("p的值为%ls",p);
    // int *q = &a;
    // printf("p的地址为%p\n",q);
    // printf("p的值为%d\n",*q);

    // int (*funpoint)(int) = &foo;
    // printf("funpoint的地址为%p\n",funpoint);
    // printf("funpoint的值为%d\n",(*funpoint)(a));
    uint64_t a = 1;
    int b = 2;
    // printf("a的地址为%p\n",(uint64_t *)&a);
    // printf("a的地址为%p\n",&a);
    // printf("a的值%d\n",*(uint64_t *)a);
    // printf("a+b的值%d\n",*(uint64_t *)a+ *(uint64_t *)b);
    printf("a的值为%lx\n",a);
    printf("a的值为%16lx\n",a);
    return 0;
}
// int foo (int b) {
//     return b;
// }