#include <stdio.h>
#define CAN1_BASE 0x001
#define CAN2_BASE 0x002
#define CAN1 CAN1_BASE
#define CAN2 CAN2_BASE
#define Can_Periperal(Canx) (Canx == CAN1 || \
                             Canx == CAN2)
int main()
{
    if (Can_Periperal(CAN2) == CAN1){
        printf("Hien Bach choosed CAN1\n");
    }
    else{
        printf("Hien Bach choosed CAN2\n");
    }
    return 0;
}