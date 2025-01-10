#include<stdio.h>
#include<stdlib.h>

int main()
{
    // Stack memory
    int a = 50;
    char b = 'A';

    // Heap memory
    int *prt = (int *)malloc(sizeof(int));
    *prt = a;
    printf("a (stack): %d\n", a);
    printf("b (stack): %c\n", b);
    printf("Dia chi prt (stack): %p\n", prt);
    printf("Gia tri prt (heap): %d\n", *prt);

    free(prt);
    return 0;
}