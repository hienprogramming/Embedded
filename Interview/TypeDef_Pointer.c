#include <stdio.h>

#define NUMBERS 10
typedef int (*Operation)(int, int);
typedef int IntArray[NUMBERS];

int add(int a, int b) {
    return a + b;
}

int subtraction(int a, int b) {
    return a - b;
}

int main() {
    // Sử dụng typedef cho con trỏ hàm
    printf("--------------------------------\n");
    printf("EXAMPLE 1: Sử dụng typedef cho con trỏ hàm\n");
    printf("--------------------------------\n");
    Operation op;
    op = add;
    int result_add = op(3, 4);
    printf("Adding of function pointer with typedef: %d\n", result_add);

    op = subtraction;
    int result_sub = op(10, 4);
    printf("Subtraction of function pointer with typedef: %d\n", result_sub);
    printf("--------------------------------\n");

    // Sử dụng typedef cho mảng
    printf("EXAMPLE 2: Sử dụng typedef cho mảng\n");
    printf("--------------------------------\n");
    IntArray arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    printf("Print all of Array\n");
    for(int i = 0; i < NUMBERS; i++) {
        printf("arr[%d] = %d\n", i, arr[i]);
    }

    return 0;
}
