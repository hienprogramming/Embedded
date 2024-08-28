#include "Lcd.h"
#include "stm32f10x.h"

void SysTick_Handler(void);
void delay_ms(uint32_t ms);

volatile uint32_t msTicks = 0;

void SysTick_Handler(void) {
    msTicks++;
}

void delay_ms(uint32_t ms) {
    uint32_t currentTicks = msTicks;
    while ((msTicks - currentTicks) < ms);
}