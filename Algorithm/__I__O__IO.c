#include <stdio.h>
#include <stdint.h>

#define __I  volatile const  // Chỉ đọc (Input)
#define __O  volatile        // Chỉ ghi (Output)
#define __IO volatile        // Đọc/ghi (Input/Output)


// Định nghĩa kiểu REG_TypeDef
typedef struct 
{
    __I  uint32_t CTRL;   // Thanh ghi điều khiển (chỉ đọc)
    __O  uint32_t STATUS; // Thanh ghi trạng thái (chỉ ghi)
    __IO uint32_t CMD;    // Thanh ghi lệnh (đọc/ghi)
} REG_TypeDef;

// Giả lập bộ nhớ cho thanh ghi
REG_TypeDef fake_register = {0x12345678, 0, 0};  // Giá trị mặc định

// Macro trỏ tới thanh ghi (giả lập)
#define REG  ((REG_TypeDef *)&fake_register)
// #define REG  ((REG_TypeDef *)0x40001000)
// Hàm mô phỏng đọc thanh ghi
void read_registers()
{
    printf("CTRL Register:  0x%08X\n", REG->CTRL);
    printf("CMD Register:   0x%08X\n", REG->CMD);
}

// Hàm mô phỏng ghi lệnh vào thanh ghi CMD
void write_command(uint32_t cmd)
{
    REG->CMD = cmd;
    printf("CMD written:    0x%08X\n", REG->CMD);
}

int main()
{
    printf("Initial Register State:\n");
    read_registers();

    printf("\nWriting CMD register...\n");
    write_command(0xAABBCCDD);

    printf("\nUpdated Register State:\n");
    read_registers();

    return 0;
}
