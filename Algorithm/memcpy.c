
// memcpy thực hiện việc copy data số tới vùng nhớ khác để xử lí
#include<stdio.h>
#include<stdlib.h> // Quản lí bộ nhớ với malloc(), calloc(), realloc(), free(), toán học
#include <string.h> // Quản lí và chứa memcpy

typedef unsigned char uint8_t;
typedef unsigned int uint16_t;
void read_from_sensor(uint8_t *data)
{
    data[0] = 0x10; // Send first byte
    data[1] = 0x30; // Send second byte
}

float convert_to_C(uint16_t dataraw)
{
    return (float) (dataraw/10.0);
}
int main()
{
    uint8_t gpio_data[2];
    uint16_t dataraw;
    float data_C;
    read_from_sensor(gpio_data);

    printf("sizeof gpio_data: %d\n", sizeof(gpio_data));

    memcpy(&dataraw, gpio_data, sizeof(gpio_data));
    data_C = convert_to_C(dataraw);
    printf("data_C = %.2f\n", data_C);
    
    return 1;  
}

