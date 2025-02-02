#include<stdio.h>
#include <stdlib.h> // Thêm thư viện này để sử dụng malloc và free
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

// Con trỏ hàm
void Pointer_of_func(int a)
{
    printf("\nIII. Pointer of Function!\n");
    printf("----------------------\n");
    printf("Point of function: %d\n", a);
    printf("----------------------\n");
}

// Con trỏ tới con trỏ
void Pointer_to_pointer()
{
    int a = 10;
    int *p = &a;
    int **pinp = &p;
    printf("\nIV. Pointer to pointer!\n");
    printf("%p\n", &a);
    printf("%p\n", &p);
    printf("----------------------\n");
}

// Con trỏ và cấu trúc
void Pointer_to_struct()
{
    typedef struct Pointer
    {
        int x, y;
    }Point;
    Point p = {10, 20};
    Point *p_prt = &p;
    int c = 10;
    int *p_test = &c;
    printf("Address c: %p, value = %d", &p_test, *p_test);
    printf("\nV. Pointer and Struct!\n");
    printf("Address p0: %p, value = %d\n", &(p_prt->x), p_prt->x);
    printf("Address p0: %p, value = %d\n", (void*)&(p_prt->x), p_prt->x);
    printf("Address p1: %p, value = %d\n", &(p_prt->y), p_prt->y);
    printf("Address p1: %p, value = %d\n", (void*)&(p_prt->y), p_prt->y);
    printf("----------------------\n");

}

// Con trỏ động và cấp phát bộ nhớ động
/*Cấp phát và giải phóng bộ nhớ: Sử dụng malloc, calloc, realloc, và free.*/
// Con trỏ động và cấp phát bộ nhớ động
void Allocation_memory()
{
    printf("\nVI. Con trỏ động và cấp phát bộ nhớ động!\n");
    int *p = (int*)malloc(sizeof(int) * 5); // Cấp phát bộ nhớ cho mảng 5 phần tử
    if (p == NULL) {
        printf("Memory allocation failed\n");
        return;
    } else {
        printf("Memory allocation is successful. Address: %p\n", (void*)p);
    }

    // Gán giá trị cho mảng động
    for (int i = 0; i < 5; i++) {
        p[i] = i + 1;
    }

    // In ra các giá trị trong mảng
    for (int i = 0; i < 5; i++) {
        printf("p[%d] = %p, value = %d\n", i, &p[i], p[i]);
    }

    // Giải phóng bộ nhớ
    free(p);
    p = NULL; // Đặt con trỏ về NULL sau khi giải phóng
    // Kiểm tra xem p có phải là NULL hay không
    if (p == NULL) {
        printf("Memory has been freed successfully and pointer is set to NULL\n");
    } else {
        printf("Failed to free memory\n");
    }
    printf("----------------------\n");
}
int main()
{
    intro_pointer();

    pointer_array();

    void (*Pointer_func)(int) = Pointer_of_func;
    // printf("Address: %p, Value: %p", &Pointer_of_func, (int*)Pointer_func);
    printf("Address: %p\n", &Pointer_of_func);
    printf("Address: %p\n", (void*)Pointer_func);
    Pointer_func(4);
    
    Pointer_to_pointer();

    Pointer_to_struct();

    Allocation_memory();
    return 0;
}

