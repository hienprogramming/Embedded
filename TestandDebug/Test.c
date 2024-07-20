

// #include <stdio.h>
// typedef unsigned int       uint32_t;
// // Định nghĩa struct để lưu trữ thông tin của một thanh ghi
// typedef struct {
//     volatile uint32_t CR;  // Thanh ghi điều khiển
//     volatile uint32_t SR;  // Thanh ghi trạng thái
//     volatile uint32_t DR;  // Thanh ghi dữ liệu
// } USART_TypeDef;

// int main() {
//     // Khai báo con trỏ trỏ đến địa chỉ của thanh ghi USART
//     USART_TypeDef* USART1 = (USART_TypeDef*)0x40013800;

//     // Truy cập và sử dụng các thanh ghi
//     USART1->CR = 0x00000001; // Thiết lập bit enable trong thanh ghi điều khiển
//     uint32_t status = USART1->SR; // Đọc giá trị từ thanh ghi trạng thái
//     USART1->DR = 0x41; // Ghi dữ liệu vào thanh ghi dữ liệu

//     return 0;
// }

// CR, SR, DR: 32 bits
/*
 CR: Thiết lập bit enable trong thanh ghi điều khiển bằng bit đầu tiên.
 Chỉ được gọi 1 lần đầu tiên để enable UART. Nếu là bit 1 thì giữ cho giao tiếp.
 Nếu không thì lỗi giao thức. End chương trình với địa chỉ sai.

 SR: Đọc trạng thái thanh ghi. Nếu CR là enable thì thanh ghi SR ok và ngc lại

 DR: SR ok thì cho gửi data, còn không thì in ra lỗi
*/

// 1byte -> 8bit
// 2^4 = 16
// -> số 1hex = 4 byte

#include <stdio.h>
#include <stdbool.h>
#define True 1
#define False 0
#define E_OK True;
#define E_NOT_OK False;

typedef unsigned int uint32_t;
typedef struct{
    uint32_t CR;
    bool    SR;
    uint32_t DR;
}UATR_Typedef;

int init_UART(bool flag)
{
    if (flag == True)
    {
        return E_OK;
    }
    else
    {
        return E_NOT_OK;
    }
}
int main()
{
    UATR_Typedef UART_instance = {0};
    UATR_Typedef* UART = &UART_instance;
    static bool flag_CR = False;
    UART->CR = 0x00000001;
    if (UART->CR & 0x00000002){
        flag_CR = True;
    }
    else {
        flag_CR = False;
    }

    // Check enable UART?
    do{
        UART->SR = True;
        if(UART->SR == True)
        {
            UART->DR = 4;
        }
        printf("\nInit for UART\n");
        printf("Address of register is: %p", &(UART));
        printf("\nValue is: %d", UART->DR);
    }while(init_UART(flag_CR));
    printf("\nError UART");
    printf("\nAddress error in: %p", &(UART));

    return 0;
}

// #include <stdio.h>
// #include <stdbool.h>

// #define True 1
// #define False 0
// #define E_OK True
// #define E_NOT_OK False

// typedef unsigned int uint32_t;
// typedef struct {
//     volatile uint32_t CR;
//     volatile bool SR;
//     volatile uint32_t DR;
// } UART_Typedef;

// int init_UART(bool flag)
// {
//     if (flag == True)
//     {
//         return E_OK;
//     }
//     else
//     {
//         return E_NOT_OK;
//     }
// }

// int main()
// {
//     printf("Hello");
//     UART_Typedef UART_instance = {0};
//     UART_Typedef* UART = &UART_instance;
//     static bool flag_CR = False;

//     // Thiết lập bit enable trong thanh ghi điều khiển CR
//     UART->CR = 0x00000001;
//     if (UART->CR & 0x00000001)
//     {
//         flag_CR = True;
//     }
//     else
//     {
//         printf("\nProtocol error");
//         printf("\nAddress error in: %p", (void*)UART);
//         return -1; // Kết thúc chương trình với địa chỉ sai
//     }

//     // Kiểm tra và enable UART chỉ một lần
//     if (init_UART(flag_CR) == E_NOT_OK)
//     {
//         printf("\nError UART");
//         printf("\nAddress error in: %p", (void*)UART);
//         return -1; // Kết thúc chương trình với địa chỉ sai
//     }

//     // Đọc trạng thái thanh ghi SR
//     UART->SR = (flag_CR == True) ? True : False;

//     // Gửi data nếu SR ok
//     if (UART->SR == True)
//     {
//         UART->DR = 4;
//         printf("\nInit is done and no error\n");
//         printf("Address of register is: %p", (void*)UART);
//         printf("\nValue is: %d", UART->DR);
//     }
//     else
//     {
//         printf("\nError in UART status register");
//     }

//     return 0;
// }