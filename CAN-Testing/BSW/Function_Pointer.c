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

#include<stdio.h>

int addmore(int a, int b)
{
    return a+b;
}

int substract(int a, int b)
{
    return a-b;
}

int (*operation)(int, int);

int main(){
    operation = addmore;
    printf("add function: %d", operation(3,4));
    operation = substract;
    printf("add function: %d", operation(4,2));
}