#include "stm32f10x.h"

void GPIO_Config(void);
void SysTick_Handler(void);
void delay_ms(uint32_t ms);

volatile uint32_t msTicks = 0;

int main(void) {
    // Cấu hình SysTick
    if (SysTick_Config(SystemCoreClock / 1000)) {
        while (1); // Lỗi nếu không thể cấu hình
    }

    // Cấu hình GPIO
    GPIO_Config();

    while (1) {
        GPIO_SetBits(GPIOC, GPIO_Pin_13);  // Bật LED
        delay_ms(1000);                     // Đợi 500ms
        GPIO_ResetBits(GPIOC, GPIO_Pin_13);// Tắt LED
        delay_ms(1000);                     // Đợi 500ms
    }
}

void GPIO_Config(void) {
    GPIO_InitTypeDef GPIO_InitStructure;

    // Bật clock cho GPIOC
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

    // Cấu hình PC13 làm output push-pull
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}

void SysTick_Handler(void) {
    msTicks++;
}

void delay_ms(uint32_t ms) {
    uint32_t currentTicks = msTicks;
    while ((msTicks - currentTicks) < ms);
}
