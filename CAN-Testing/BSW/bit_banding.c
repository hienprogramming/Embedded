#include<stdio.h>
#include<stdlib.h>

#define GPIOA_DATA_BASE 0X00030303
#define GPIOA_DATA_BIT_5TH (GPIOA_DATA_BASE + 5 << 2)

int main()
{
    int read_data = *(volatile int*) GPIOA_DATA_BIT_5TH;
    printf("read_data: %d\n", read_data);
    // turn on bit 5th
    *(volatile int*) GPIOA_DATA_BIT_5TH = 1;
    // turn off bit 5th
    *(volatile int*) GPIOA_DATA_BIT_5TH = 0;
    return 1;
}


#include <stdio.h>

#define LED_PIN 0x02 // Bit thứ 1

int main() {
    int port = 0x00; // Giá trị ban đầu của port

    // Bật LED
    port |= LED_PIN; // Thiết lập bit thứ 1

    // Tắt LED
    port &= ~LED_PIN; // Xóa bỏ bit thứ 1

    // Kiểm tra trạng thái LED
    if (port & LED_PIN) {
        printf("LED đang bật\n");
    } else {
        printf("LED đang tắt\n");
    }

    return 0;
}