#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h> 
#include <time.h> // For seeding rand()

typedef uint16_t CanIDType, CanHwHandleType;

typedef struct {
    CanIDType CanID;
    CanHwHandleType HwObjectHandle; // hoh
    uint8_t CanControllerId;        // CanHS and CanFD, it's depend on HW (chip set) supported
} CanHwType;

typedef struct {
    uint8_t SduData[8]; // Fixed size array for actual data storage
    uint8_t SduLengh;   // Length of the data
} PduInforType;

void SimulationCanHwObject(CanHwType *MailBox) {
    if (MailBox == NULL) {
        printf("Error: MailBox is NULL\n");
        return;
    }

    MailBox->CanID = 0x7FF;           // Simulated CAN ID
    MailBox->HwObjectHandle = 0x01;   // Simulated Hardware Object Handle
    MailBox->CanControllerId = 0x00;  // Simulated Controller ID
}

void SimulationPduInfor(PduInforType *PduInfor) {
    if (PduInfor == NULL) {
        printf("Error: PduInfor is NULL\n");
        return;
    }

    // Generate a random number of data bytes (0 to 8)
    uint8_t numofData = rand() % 9; // Ensure numofData is between 0 and 8
    PduInfor->SduLengh = numofData;

    // Populate SduData with random bytes
    for (int i = 0; i < numofData; i++) {
        PduInfor->SduData[i] = rand() % 256; // Random byte between 0x00 and 0xFF
    }

    // printf("Simulated PduInfor: Length = %d, Data = ", PduInfor->SduLengh);
    // for (int i = 0; i < PduInfor->SduLengh; i++) {
    //     printf("0x%02X ", PduInfor->SduData[i]);
    // }
    printf("\n");
}

uint8_t CanRxIndication_Def(
    const CanHwType *MailBox, 
    const PduInforType *PduInfor
) {
    if (MailBox == NULL || PduInfor == NULL) {
        printf("Error: Null parameter passed to CanRxIndication_Def\n");
        return 0; // Failure
    }

    // HW Filter
    if ((MailBox->CanID & 0x7FF) == 0x7FF) { // Apply mask and compare
        printf("CanID is allowed\n");
        printf("Data of 0x%X is: ", MailBox->CanID);
        for (uint8_t i = 0; i < PduInfor->SduLengh; i++) {
            printf("0x%02X ", PduInfor->SduData[i]);
        }
        printf("\n");
        return 1; // Indicating success
    } else {
        printf("CanID is not allowed\n");
        return 0; // Indicating failure
    }
}

int main() {
    srand(time(NULL)); // Seed the random number generator

    CanHwType mailbox;
    PduInforType pduInfor;

    SimulationPduInfor(&pduInfor);
    SimulationCanHwObject(&mailbox);

    uint8_t result = CanRxIndication_Def(&mailbox, &pduInfor);
    printf("The result: %d\n", result);

    return 0;
}
