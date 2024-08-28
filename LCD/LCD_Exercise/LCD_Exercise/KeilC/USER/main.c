#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "lcd16x2.h"
#include "delay.h"

void Pin13_Led()
{
	GPIO_SetBits(GPIOC, GPIO_Pin_13);
	DelayMs(500);
	GPIO_ResetBits(GPIOC, GPIO_Pin_13);
	DelayMs(500);
}

void GPIO_Config(void) {
    GPIO_InitTypeDef GPIO_InitStructure;

    // B?t clock cho GPIOC
    // RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    // C?u hình PC13 làm output push-pull
    // GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}


int main(void)
{
    // Delay initialization
    DelayInit();
    // LCD initialization
    LCD_Init();
		GPIO_Config();
			  int i; 
        LCD_Gotoxy(6,0);
        LCD_Puts("Hien Bach");
			  for(i = 0; i < 6; i++)
			  {
					LCD_SendCommand(0x18);
					DelayMs(20);
				}
			
    while(1)
		{
			int i; 
        LCD_Gotoxy(0,0);
			  for(i = 0; i < 12; i++)
			  {
					LCD_SendCommand(0x1C);
					DelayMs(20);
				}
				Pin13_Led();
				DelayMs(10);
				for(i = 0; i < 12; i++)
			  {
					LCD_SendCommand(0x18);
					DelayMs(20);
				}
		}

    		

}

