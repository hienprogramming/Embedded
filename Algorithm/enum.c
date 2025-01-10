#include<stdio.h>

typedef enum{
    LEDOFF,
    LEDON,
    LED_NN
}LedState;

int main()
{
    LedState LS = LEDOFF;
    if(LS == LEDOFF){
        printf("Đèn LED đang bật\n");
    }
    else{
        printf("Đèn LED đang tắt\n");
    }
}