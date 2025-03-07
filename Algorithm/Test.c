// #include <stdio.h>
// #include <stdint.h>

// #define __I  volatile const  // Chỉ đọc (Input)
// #define __O  volatile        // Chỉ ghi (Output)
// #define __IO volatile        // Đọc/ghi (Input/Output)


// // Định nghĩa kiểu REG_TypeDef
// typedef struct 
// {
//     __I  uint32_t CTRL;   // Thanh ghi điều khiển (chỉ đọc)
//     __O  uint32_t STATUS; // Thanh ghi trạng thái (chỉ ghi)
//     __IO uint32_t CMD;    // Thanh ghi lệnh (đọc/ghi)
// } REG_TypeDef;

// // Giả lập bộ nhớ cho thanh ghi
// REG_TypeDef fake_register = {0x12345678, 0, 0};  // Giá trị mặc định

// // Macro trỏ tới thanh ghi (giả lập)
// #define REG  ((REG_TypeDef *)&fake_register)

// // Hàm mô phỏng đọc thanh ghi
// void read_registers()
// {
//     printf("CTRL Register:  0x%08X\n", REG->CTRL);
//     printf("CMD Register:   0x%08X\n", REG->CMD);
// }

// // Hàm mô phỏng ghi lệnh vào thanh ghi CMD
// void write_command(uint32_t cmd)
// {
//     REG->CMD = cmd;
//     printf("CMD written:    0x%08X\n", REG->CMD);
// }

// int main()
// {
//     printf("Initial Register State:\n");
//     read_registers();

//     printf("\nWriting CMD register...\n");
//     write_command(0xAABBCCDD);

//     printf("\nUpdated Register State:\n");
//     read_registers();

//     return 0;
// }


#include <stdio.h>
#include <stdint.h>

void Pointer_Is_Assigned_Array()
{
    uint8_t arr[4];
    uint8_t *prt = arr;
    printf("Enter 4 numbers (0-255): \n");
    
    // Lý do phải dùng int temp thay vì uint8_t temp:
    // 1. scanf("%u", &temp) với uint8_t temp sẽ gây lỗi vì scanf cần một buffer đủ lớn (int)
    // để lưu giá trị tạm thời trước khi kiểm tra range
    // 2. Nếu dùng uint8_t, khi người dùng nhập số >255, giá trị sẽ bị tràn và wrap around
    // thay vì cho phép ta kiểm tra range một cách chính xác
    // 3. Sau khi kiểm tra range hợp lệ (0-255), ta mới ép kiểu an toàn về uint8_t
    for (uint8_t i = 0; i < 4; i++){
        int temp;
        uint8_t result = scanf("%u", &temp);
        arr[i] = (uint8_t)temp;
    }

    
    printf("\nUsing array indexing:\n");
    for (int i = 0; i < 4; i++){
        printf("Address of arr[%d]: %p\n", i, (void *)&arr[i]);
        printf("Value of arr[%d]: %d\n\n", i, arr[i]);
    }
    
    printf("\nUsing pointer arithmetic:\n");
    for (int i = 0; i < 4; i++){
        printf("Address of pointer[%d]: %p\n", i, (void *)(prt + i));
        printf("Value of pointer[%d]: %d\n\n", i, *(prt + i));
    }
}

void def_pointer(){
    int array[5] = {1, 2, 3, 4, 5};
    int *prt = array;
    for (int i = 0; i < sizeof(array) / sizeof(array[0]); i++){
        scanf("%d", &array[i]);
    }
    for (int i = 0; i < sizeof(array) / sizeof(array[0]); i++){
        printf("Address array[%d]: %p\n", i, (prt + i));
        printf("Data array[%d]: %d\n", i, *(prt + i));
    }
}

int main()
{
    def_pointer();
}