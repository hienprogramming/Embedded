// ghi vao thanh ghi gpio 8bit co dia chi la 0x1000 gia tri 0x55
#include <stdio.h>
typedef unsigned char uint8_t;

int main() {
    printf("Hello world");
    uint8_t data = 0x55; // Khai báo biến data kiểu unsigned char
    uint8_t* pointer = (uint8_t*)0x1000; // Cast to uint8_t*
    * pointer = data; // Ghi giá trị của biến data vào địa chỉ mà ptr trỏ tới
    pointer = (uint8_t*)0x10101;
    * pointer = 0xAA;
    printf("%d: ", data);
}