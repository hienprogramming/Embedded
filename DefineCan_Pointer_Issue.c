#include <stdio.h>
#include <stdint.h>
#define CAN1_BASE 0x001
#define CAN2_BASE 0x002
#define CAN1 CAN1_BASE
#define CAN2 CAN2_BASE
#define Can_Periperal(Canx) (Canx == CAN1 || \
                             Canx == CAN2)

typedef struct {
    uint32_t StdId;
    uint32_t ExtId;
    uint8_t IDE;
    uint8_t DLC;
}CanType;


void CAN_Receive(uint8_t Canx, CanType *Ressage){
    if (!(Can_Periperal(Canx))){
        printf("Invalid CAN periperal: 0x%X", Canx);
        return;
    }
    else{
        printf("Hien handsome\n");
    }
}

int main()
{
    // CanType message;
    // while(1){
    //     if (Can_Periperal(CAN1)){
    //         printf("Hien Bach choosed CAN1\n");
    //         CAN_Receive(CAN1, &message);
    //     }
    //     else{
    //         printf("Hien Bach choosed CAN2\n");
    //     }
    //     for(volatile int i = 0; i < 900000000; i++);
    // }

    // return 0;




    /*-------------------------------------------------------*/
    // Nếu muốn sử dụng con trỏ cho messge với type là CanType
    /*-------------------------------------------------------*/
    while (1) {
        CanType *message = (CanType *)malloc(sizeof(CanType)); // Cấp phát bộ nhớ động
        if (message == NULL) {
            printf("Memory allocation failed\n");
            return -1; // Thoát nếu cấp phát thất bại
        }

        if (Can_Periperal(CAN1)) {
            printf("Hien Bach choosed CAN1\n");
            CAN_Receive(CAN1, message); // Truyền con trỏ `message`
        } else {
            printf("Hien Bach choosed CAN2\n");
        }

        free(message); // Giải phóng bộ nhớ sau khi sử dụng
        for (volatile int i = 0; i < 900000000; i++); // Delay giả lập
    }

    return 0;

}