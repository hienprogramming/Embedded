#include<stdio.h>

int add(int a, int b)
{
    return a + b;
}
int substract(int a, int b)
{
    return a - b;
}
int (*Opreration) (int, int);
int main()
{
    Opreration = add;
    printf("Add: %d\n", Opreration(5, 3));
    Opreration = substract;
    printf("substract: %d\n", Opreration(5, 3));
}