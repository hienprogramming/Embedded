#include <stdio.h>
#include <stdint.h>
#define CAN1_BASE 0x001
#define CAN2_BASE 0x002
#define CAN1 CAN1_BASE
#define CAN2 CAN2_BASE
#define Can_Periperal(Canx) (Canx == CAN1 || \
                             Canx == CAN2)
#define USE_STD 0
#define USE_EXD 1

typedef struct {
    uint32_t StdId;
    uint32_t ExtId;
    uint16_t IDE;
    uint8_t DLC;
}CanType;


void CAN_Receive(uint8_t Canx, CanType *Message, uint8_t TypeCan_STD_EXD){
    if (!(Can_Periperal(Canx))){
        printf("Invalid CAN periperal: 0x%X", Canx);
        return;
    }
    Message->StdId = TypeCan_STD_EXD;
    Message->ExtId = TypeCan_STD_EXD;
    Message->IDE = 600;
    Message->DLC = 8; //default;
    if (Message->StdId == USE_STD){
        printf("Type of Can: %d\n", Message->StdId);
    }
    else if (Message->StdId == USE_EXD)
    {
        printf("Type of Can: %d\n", Message->StdId);
    }
    printf("Message ID: %d\n", Message->IDE);
    printf("Data length of message: %d\n", Message->DLC);
}

int main()
{
    // Solution nằm ở đây
    CanType message;
    while(1){
        if (Can_Periperal(CAN1)){
            printf("Hien Bach choosed CAN1\n");
            CAN_Receive(CAN1, &message, USE_STD);
        }
        else{
            printf("Hien Bach choosed CAN2\n");
        }
        for(volatile int i = 0; i < 900000000; i++);
    }

    return 0;
}