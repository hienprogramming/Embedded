#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BASEADD_RESGPIOA (0x00400000)

#define BASEADD_RESGPIOA_OFFET (0X0200)

#define RESGISTER (*(volatile uint32_t *)(BASEADD_RESGPIOA + BASEADD_RESGPIOA_OFFET))

int main()
{
    volatile uint32_t bit1st ;
    RESGISTER |= (1 << 0);
    bit1st = RESGISTER;
}