#include "stm32f10x.h"
#include "stm32f10x_i2c.h"

void I2C_Configuration(void) {
    I2C_InitTypeDef I2C_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    
    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
    I2C_InitStructure.I2C_OwnAddress1 = 0x00;
    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_InitStructure.I2C_ClockSpeed = 100000;
    
    I2C_Init(I2C1, &I2C_InitStructure);
    I2C_Cmd(I2C1, ENABLE);
}


#include "stm32f10x.h"

#define LCD_ADDR 0x4E // Địa chỉ I2C của PCF8574T

void I2C_Write(uint8_t data) {
    while (I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));
    
    I2C_GenerateSTART(I2C1, ENABLE);
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
    
    I2C_Send7bitAddress(I2C1, LCD_ADDR, I2C_Direction_Transmitter);
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
    
    I2C_SendData(I2C1, data);
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
    
    I2C_GenerateSTOP(I2C1, ENABLE);
}

void LCD_SendCommand(uint8_t cmd) {
    uint8_t highNibble = cmd & 0xF0;
    uint8_t lowNibble = (cmd << 4) & 0xF0;
    
    I2C_Write(highNibble | 0x0C);
    I2C_Write(highNibble | 0x08);
    I2C_Write(lowNibble | 0x0C);
    I2C_Write(lowNibble | 0x08);
}

void LCD_SendData(uint8_t data) {
    uint8_t highNibble = data & 0xF0;
    uint8_t lowNibble = (data << 4) & 0xF0;
    
    I2C_Write(highNibble | 0x0D);
    I2C_Write(highNibble | 0x09);
    I2C_Write(lowNibble | 0x0D);
    I2C_Write(lowNibble | 0x09);
}

void LCD_Init(void) {
    LCD_SendCommand(0x33);
    LCD_SendCommand(0x32);
    LCD_SendCommand(0x28);
    LCD_SendCommand(0x0C);
    LCD_SendCommand(0x06);
    LCD_SendCommand(0x01);
}

void LCD_SendString(char *str) {
    while (*str) {
        LCD_SendData(*str++);
    }
}

int main(void) {
    I2C_Configuration();
    LCD_Init();

    LCD_SendString("Hien Bach");

    while (1) {
        // Vòng lặp chính
    }
}
