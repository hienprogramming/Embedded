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