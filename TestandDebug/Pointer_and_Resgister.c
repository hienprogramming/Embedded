#include <stdio.h>
typedef unsigned char uint8_t;

// Hàm đọc giá trị từ register tại địa chỉ cho trước
int read_register(uintptr_t reg_addr) {
    int value;
    // Đọc giá trị từ địa chỉ register
    value = *(int *)reg_addr;
    return value;
}

// Hàm ghi giá trị vào register tại địa chỉ cho trước
void write_register(uintptr_t reg_addr, int value) {
    // Ghi giá trị vào địa chỉ register
    *(int *)reg_addr = value;
}

int main() {
    uintptr_t reg_addr = 0x1000; // Địa chỉ thanh ghi có thể thay đổi

    // Đọc giá trị từ register
    int value = read_register(reg_addr);
    printf("Giá trị của register: %d\n", value);

    // Ghi giá trị vào register
    write_register(reg_addr, 10);

    return 0;
}