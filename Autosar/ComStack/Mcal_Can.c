#include <stdio.h>
#include "Mcal_Can.h"
#include "CanIf.h" // Để gọi lên lớp trên
#include <stdlib.h>

// Định nghĩa kiểu dữ liệu cơ bản
typedef unsigned char uint8;
typedef unsigned short uint16;


/**
 * @brief Mô phỏng việc ghi một khung tin CAN ra bus.
 * Trong thực tế, hàm này sẽ tương tác với các thanh ghi của bộ điều khiển CAN.
 * @param CanId ID của khung tin CAN.
 * @param PduInfoPtr Con trỏ chứa dữ liệu và độ dài dữ liệu (DLC).
 */
void Mcal_Can_Write(uint16 CanId, const PduInfoType* PduInfoPtr) {
    printf("[MCAL_CAN] Writing to bus: ID=0x%X, DLC=%d, Data=[", CanId, PduInfoPtr->SduLength);
    for (uint8 i = 0; i < PduInfoPtr->SduLength; ++i) {
        printf("0x%02X ", PduInfoPtr->SduDataPtr[i]);
    }
    printf("]\n");

    // Simulate successful transmission immediately and call CanIf_TxConfirmation
    CanIf_TxConfirmation(0); // 0 is assumed PDU ID
}

///
// Hàm tạo message giả lập ngẫu nhiên Rx
// PduInfoType generate_random_message_Rx() {
//     PduInfoType pdu;
//     /*
//      * SduDataPtr is defined as a pointer in `PduInfoType`.
//      * The original code wrote into `pdu.SduDataPtr[i]` without
//      * assigning the pointer, causing a segmentation fault.
//      *
//      * Use a static buffer so the returned PduInfoType points to
//      * valid storage that remains alive after the function returns.
//      * This keeps the change minimal; for a production system you
//      * might instead allocate memory and document ownership or
//      * change the API to copy into a caller-provided buffer.
//      */
//     static uint8 static_data[8];
//     pdu.SduDataPtr = static_data;
//     pdu.SduLength = 8;                     // Cố định DLC là 8 byte
//     for (int i = 0; i < 8; i++){
//         pdu.SduDataPtr[i] = (uint8)(rand() % 256);  // Random từng byte trong khoảng 0x00 - 0xFF
//     }
//     return pdu;
// }
// viết hàm RanDom_CanId   
// uint16 RanDom_CanId() {
//     uint16 CanId;
//     CanId = 0x600 + (rand() % 49); // Random ID từ 0x600 đến 0x649
//     return CanId;
// }

///
///

/**
 * @brief Mô phỏng một hàm được gọi bởi main loop để giả lập việc nhận được 1 frame CAN.
 * Trong thực tế, đây sẽ là một trình phục vụ ngắt (ISR) được kích hoạt bởi phần cứng.
 */
void Mcal_Can_SimulateRx() {
    printf("\n--- [MCAL_CAN] Simulating received frame from bus ---\n");
    // Simulated received data
    uint8 rx_data[8] = {0x12, 0x34, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    PduInfoType rxPdu;
    rxPdu.SduDataPtr = rx_data;
    rxPdu.SduLength = 2;

    // PduInfoType rxPdu = generate_random_message_Rx();
    // uint16 CanId = RanDom_CanId();
    // Call upper layer (CanIf) to notify new data
    // 0x101 is the CanId of received frame
    // CanIf_RxIndication(CanId, &rxPdu);
    CanIf_RxIndication(0x101, &rxPdu);
}

