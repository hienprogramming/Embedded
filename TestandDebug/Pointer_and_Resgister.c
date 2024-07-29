#include<stdio.h>
// Function for read value of register
int read_value_reg(uintptr_t addr)
{
    int value;
    value = *(uintptr_t*) addr;
    return value;
}

void write_value_reg(uintptr_t addr, int value)
{
    *(uintptr_t*) addr = value;
}
int main()
{
    // Function for read value of register
    read_value_reg(0x1000);
    // Function for write value of register
    write_value_reg(0x1010, 100);
    return 0;
}




// #include <stdint.h>
// #include <stdio.h>

// // Giả định rằng chúng ta có một vi điều khiển với các thanh ghi
// #define REG_CONTROL (*(volatile uint32_t*)0x40000000)
// #define REG_STATUS  (*(volatile uint32_t*)0x40000004)

// // Bitmask cho các bit trong thanh ghi điều khiển
// #define CONTROL_ENABLE (1 << 0)
// #define CONTROL_RESET  (1 << 1)

// void enable_device() {
//     REG_CONTROL |= CONTROL_ENABLE; // Bật thiết bị
// }

// void reset_device() {
//     REG_CONTROL |= CONTROL_RESET; // Đặt lại thiết bị
//     REG_CONTROL &= ~CONTROL_RESET; // Xóa bit đặt lại
// }

// uint32_t read_status() {
//     return REG_STATUS; // Đọc trạng thái
// }

// int main() {
//     enable_device();
//     reset_device();

//     uint32_t status = read_status();
//     printf("Device Status: %u\n", status);

//     return 0;
// }