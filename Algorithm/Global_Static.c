#include<stdio.h>
#include<stdlib.h>

int global_var = 10;
static int static_var = 10;

void function1()
{
    int local_var = 10;
    static int local_var_static = 10;
    printf("global_var co gia tri: %d\n", global_var);
    printf("static_var co gia tri: %d\n", static_var);
    printf("local_var co gia tri: %d\n", local_var);
    printf("local_var_static co gia tri: %d\n", local_var_static);

    global_var++;
    static_var++;
    local_var++;
    local_var_static++;
}

void function2()
{
    int local_var = 10;
    static int local_var_static = 10;
    printf("global_var co gia tri: %d\n", global_var);
    printf("static_var co gia tri: %d\n", static_var);
    printf("local_var co gia tri: %d\n", local_var);
    printf("local_var_static co gia tri: %d\n", local_var_static);

    global_var++;
    static_var++;
    local_var++;
    local_var_static++;
}
int main()
{
    printf("Function1\n");
    function1();
    printf("Function1+1\n");
    function1();
    printf("Function2\n");
    function2();
    printf("Function2+2\n");
    function2();
    return 0;
}