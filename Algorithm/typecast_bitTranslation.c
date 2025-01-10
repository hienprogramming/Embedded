/*
    Sensor 16bit
    gpio 8bit
    data transfer from Sensor to gpio need to be typecasted
*/
#include<stdio.h>
typedef unsigned int uint16_t;
typedef unsigned char uint8_t;
#define GPIOA_DATA 0X00494049
// Hàm ghi dữ liệu vào GPIOA
void write_Data_gpio(uint8_t data) {
    *(volatile uint8_t*)GPIOA_DATA = data;
}
int main()
{
    uint16_t sensor;  
    uint8_t gpioA;
    uint8_t bytelow, bytehigh;
    
    sensor = 500;

    bytelow =  (sensor) & 0xff;
    bytehigh =  (sensor >> 8) & 0xff;
    
    write_Data_gpio(bytelow);
    write_Data_gpio(bytehigh);

    return 1;
}

// #include<stdio.h>
// typedef unsigned int uint16_t;
// typedef unsigned char uint8_t;
// #define GPIOA_DATA 0X00494049  // Thêm dấu chấm phẩy ở đây
// // Hàm ghi dữ liệu vào GPIOA
// void write_Data_gpio(uint8_t data) {
//     *(volatile uint8_t*) GPIOA_DATA = data;
// }
// int main()
// {
//     uint16_t sensor;  
//     uint8_t gpioA;
//     uint8_t bytelow, bytehigh;
    
//     sensor = 500;

//     bytelow =  (sensor) & 0xff;
//     bytehigh =  (sensor >> 8) & 0xff;
    
//     write_Data_gpio(bytelow);
//     write_Data_gpio(bytehigh);

//     return 1;
// }