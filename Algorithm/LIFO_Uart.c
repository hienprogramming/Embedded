#include "stm32f10x.h"          // Thư viện chung của STM32F10x
#include "stm32f10x_gpio.h"     // Thư viện GPIO
#include "stm32f10x_rcc.h"      // Thư viện RCC

#define STACK_SIZE 10

// Mảng lưu trữ các sự kiện
int eventStack[STACK_SIZE];
int top = -1;  // Khi top == -1, stack rỗng

// Hàm đẩy một sự kiện vào stack
void pushEvent(int event)
{
    if(top < STACK_SIZE - 1)
    {
        eventStack[++top] = event;
    }
    else
    {
        // Xử lý lỗi tràn stack nếu cần
    }
}

// Hàm lấy một sự kiện từ stack
int popEvent(void)
{
    if(top >= 0)
    {
        return eventStack[top--];
    }
    else
    {
        // Xử lý lỗi khi stack rỗng nếu cần
        return -1;
    }
}

// Hàm Delay đơn giản (vòng lặp trễ)
void Delay(uint32_t nCount)
{
    for(; nCount != 0; nCount--);
}

int main(void)
{
    // Bật clock cho GPIOC
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

    // Cấu hình chân PC13 làm Output Push-Pull, tốc độ 2MHz
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    // Ban đầu tắt LED (trên Blue Pill LED thường tắt khi PC13 = HIGH)
    GPIO_SetBits(GPIOC, GPIO_Pin_13);

    /*  
        Đẩy các sự kiện vào stack:
          - Đẩy event 1: Bật LED
          - Đẩy event 2: Tắt LED
          - Đẩy event 1: Bật LED
        Với LIFO, sự kiện cuối cùng đẩy vào (event 1) sẽ được xử lý đầu tiên.
    */
    pushEvent(1);  // Event: Bật LED
    pushEvent(2);  // Event: Tắt LED
    pushEvent(1);  // Event: Bật LED

    // Xử lý các sự kiện theo nguyên tắc LIFO
    while(top != -1)
    {
        int event = popEvent();
        if(event == 1)
        {
            // Bật LED: PC13 ở mức RESET (0)
            GPIO_ResetBits(GPIOC, GPIO_Pin_13);
        }
        else if(event == 2)
        {
            // Tắt LED: PC13 ở mức SET (1)
            GPIO_SetBits(GPIOC, GPIO_Pin_13);
        }
        // Delay để có thể quan sát được sự thay đổi của LED
        Delay(0x5FFFF);
    }

    // Vòng lặp vô hạn
    while(1)
    {
    }
}
