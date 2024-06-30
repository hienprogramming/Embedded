#include<stdio.h>

// Giới thiệu về con trỏ
void intro_pointer(){
    int a = 10;
    int *p = &a;  // 'p' là con trỏ lưu trữ địa chỉ của 'a'
    printf("-----------------\n");
    printf("I. Intro Pointer!\n");
    printf("-----------------\n");
    printf("1. Address of Pointer!\n");
    printf("%p", p);
    printf("2. \nValue of Pointer!\n");
    printf("%d", *p);
}

// Con trỏ và mảng
void pointer_array(){
    int array[5] = {1,2,3,4,5};
    int *p = array;
    printf("\n----------------------\n");
    printf("II. Pointer and Array!\n");
    printf("----------------------\n");
    for(int i = 0; i < 5; i++)
    {
        printf("Address arr[%d] = %p, value = %d\n", i, &array[i], *(p+i));
    }
    printf("\n----------------------\n");
}
int main()
{
    intro_pointer();
    pointer_array();
    return 0;
}