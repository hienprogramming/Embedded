#include <stdio.h>
#include "CanIf.h"
#include "PduR.h" // Để gọi lên PduR

// Định nghĩa các ID để mapping
#define PDU_ID_TX_ENGINEDATA 0
#define CAN_ID_TX_ENGINEDATA 0x100

#define PDU_ID_RX_VEHICLESPEED 10
#define CAN_ID_RX_VEHICLESPEED 0x101

/**
 * @brief Hàm được gọi bởi lớp trên (PduR) để yêu cầu truyền một PDU.
 * @param TxPduId ID của PDU cần truyền.
 * @param PduInfoPtr Dữ liệu của PDU.
 */
void CanIf_Transmit(uint16 TxPduId, const PduInfoType* PduInfoPtr) {
    if (TxPduId == PDU_ID_TX_ENGINEDATA) {
        printf("[CanIf] Received transmit request PDU ID %d. Sending to MCAL with CAN ID 0x%X\n", TxPduId, CAN_ID_TX_ENGINEDATA);
        Mcal_Can_Write(CAN_ID_TX_ENGINEDATA, PduInfoPtr);
    }
}

/**
 * @brief Hàm được gọi bởi CAN Driver (MCAL) khi nhận thành công một frame.
 * @param CanId ID của frame CAN nhận được.
 * @param PduInfoPtr Dữ liệu nhận được.
 */
void CanIf_RxIndication(uint16 CanId, const PduInfoType* PduInfoPtr) {
    if (CanId == CAN_ID_RX_VEHICLESPEED) {
        printf("[CanIf] Received CAN frame ID 0x%X. Notifying PduR with PDU ID %d\n", CanId, PDU_ID_RX_VEHICLESPEED);
        // Notify upper layer (PduR)
        PduR_CanIfRxIndication(PDU_ID_RX_VEHICLESPEED, PduInfoPtr);
    }
}

/**
 * @brief Hàm được gọi bởi CAN Driver (MCAL) khi một frame đã được truyền thành công.
 * @param TxPduId ID của PDU đã được xác nhận truyền xong.
 */
void CanIf_TxConfirmation(uint16 TxPduId) {
    printf("[CanIf] Received confirmation (TxConfirmation) for PDU ID %d. Notifying PduR.\n", TxPduId);
    PduR_CanIfTxConfirmation(TxPduId);
}