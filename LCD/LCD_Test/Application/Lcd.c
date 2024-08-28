#include "stm32f10x.h"
#include "stm32f10x_i2c.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "Lcd.h"

#define LCD_ADDR (0x27 << 1) // Địa chỉ I2C của module LCD, có thể thay đổi tùy thuộc vào module của bạn

void I2C_Initialize(void);
void LCD_SendCommand(uint8_t cmd);
void LCD_SendData(uint8_t data);
void LCD_Init(void);
void LCD_SendString(char *str);
void LCD_SetCursor(uint8_t row, uint8_t col);
void LCD_Clear(void);
void GPIO_Config(void);



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

int main(void)
{
	  // Cấu hình SysTick
    if (SysTick_Config(SystemCoreClock / 1000)) {
        while (1); // Lỗi nếu không thể cấu hình
    }
		
    I2C_Initialize();
    LCD_Init();
    
    LCD_SetCursor(0, 4);  // Đặt con trỏ ở hàng 0, cột 0
    LCD_SendString("Bach Hien");
    
    // // Đợi một lúc
    delay_ms(2000);
    
    LCD_Clear();  // Xóa màn hình
    
    // Cấu hình GPIO
    GPIO_Config();

    while (1) {
        GPIO_SetBits(GPIOC, GPIO_Pin_13);  // Bật LED
        delay_ms(1000);                     // Đợi 500ms
        GPIO_ResetBits(GPIOC, GPIO_Pin_13);// Tắt LED
        delay_ms(1000);                     // Đợi 500ms
		LCD_SetCursor(0, 4);
		LCD_SendString("Bach Hien");
		LCD_SetCursor(1, 4);
		LCD_SendString("Le Huyen");
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

void I2C_Initialize(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    I2C_InitTypeDef I2C_InitStruct;
    
    // Enable clock for GPIOB and I2C1
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
    
    // Configure I2C pins: SCL and SDA
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_Init(GPIOB, &GPIO_InitStruct);
    
    // Configure I2C
    I2C_InitStruct.I2C_Mode = I2C_Mode_I2C;
    I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2;
    I2C_InitStruct.I2C_OwnAddress1 = 0x00;
    I2C_InitStruct.I2C_Ack = I2C_Ack_Enable;
    I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_InitStruct.I2C_ClockSpeed = 100000; // 100kHz
    
    I2C_Init(I2C1, &I2C_InitStruct);
    I2C_Cmd(I2C1, ENABLE);
}

void LCD_SendCommand(uint8_t cmd)
{
    uint8_t data_u, data_l;
    uint8_t data_t[4];
    data_u = (cmd & 0xf0);
    data_l = ((cmd << 4) & 0xf0);
    data_t[0] = data_u | 0x0C;  //en=1, rs=0
    data_t[1] = data_u | 0x08;  //en=0, rs=0
    data_t[2] = data_l | 0x0C;  //en=1, rs=0
    data_t[3] = data_l | 0x08;  //en=0, rs=0
    
    while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));
    I2C_GenerateSTART(I2C1, ENABLE);
    
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
    I2C_Send7bitAddress(I2C1, LCD_ADDR, I2C_Direction_Transmitter);
    
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
    
    for(int i = 0; i < 4; i++)
    {
        I2C_SendData(I2C1, data_t[i]);
        while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
    }
    
    I2C_GenerateSTOP(I2C1, ENABLE);
}

void LCD_SendData(uint8_t data)
{
    uint8_t data_u, data_l;
    uint8_t data_t[4];
    data_u = (data & 0xf0);
    data_l = ((data << 4) & 0xf0);
    data_t[0] = data_u | 0x0D;  //en=1, rs=1
    data_t[1] = data_u | 0x09;  //en=0, rs=1
    data_t[2] = data_l | 0x0D;  //en=1, rs=1
    data_t[3] = data_l | 0x09;  //en=0, rs=1
    
    while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));
    I2C_GenerateSTART(I2C1, ENABLE);
    
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
    I2C_Send7bitAddress(I2C1, LCD_ADDR, I2C_Direction_Transmitter);
    
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
    
    for(int i = 0; i < 4; i++)
    {
        I2C_SendData(I2C1, data_t[i]);
        while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
    }
    
    I2C_GenerateSTOP(I2C1, ENABLE);
}

void LCD_Init(void)
{
    delay_ms(5);  // Thêm độ trễ ban đầu
    LCD_SendCommand(0x33);
    delay_ms(5);
    LCD_SendCommand(0x32);
    delay_ms(5);
    LCD_SendCommand(0x28); // Function Set: 4-bit, 2 Line, 5x7 Dots
    delay_ms(5);
    LCD_SendCommand(0x0C); // Display on, Cursor off
    delay_ms(5);
    LCD_SendCommand(0x06); // Entry mode set
    delay_ms(5);
    LCD_SendCommand(0x01); // Clear Display
    delay_ms(5);
}

void LCD_SendString(char *str)
{
    while(*str) LCD_SendData(*str++);
}

void LCD_SetCursor(uint8_t row, uint8_t col)
{
    uint8_t row_offsets[] = {0x00, 0x40, 0x14, 0x54};
    LCD_SendCommand(0x80 | (col + row_offsets[row]));
}

void LCD_Clear(void)
{
    LCD_SendCommand(0x01);  // Gửi lệnh xóa màn hình
    for(volatile int i=0; i<2000; i++);  // Đợi một chút để LCD xử lý lệnh
}