#include <stdio.h>
#include "PduR.h"
#include "Com.h"   // Gọi lên COM
#include "CanIf.h" // Gọi xuống CanIf

#define PDU_ID_COM_TX_ENGINEDATA 0
#define PDU_ID_CANIF_TX_ENGINEDATA 0

#define PDU_ID_CANIF_RX_VEHICLESPEED 10
#define PDU_ID_COM_RX_VEHICLESPEED 10

/**
 * @brief Hàm được gọi bởi Com để yêu cầu truyền PDU
 */
void PduR_ComTransmit(uint16 TxPduId, const PduInfoType* PduInfoPtr) {
    if (TxPduId == PDU_ID_COM_TX_ENGINEDATA) {
        printf("[PduR] Routing PDU ID %d from Com to CanIf\n", TxPduId);
        CanIf_Transmit(PDU_ID_CANIF_TX_ENGINEDATA, PduInfoPtr);
    }
}

/**
 * @brief Hàm được gọi bởi CanIf khi có PDU được nhận
 */
void PduR_CanIfRxIndication(uint16 RxPduId, const PduInfoType* PduInfoPtr) {
     if (RxPduId == PDU_ID_CANIF_RX_VEHICLESPEED) {
        printf("[PduR] Routing PDU ID %d from CanIf to Com\n", RxPduId);
        Com_RxIndication(PDU_ID_COM_RX_VEHICLESPEED, PduInfoPtr);
    }
}

/**
 * @brief Hàm được gọi bởi CanIf khi có xác nhận truyền thành công
 */
void PduR_CanIfTxConfirmation(uint16 TxPduId) {
    printf("[PduR] Routing confirmation (TxConfirmation) PDU ID %d from CanIf to Com\n", TxPduId);
    Com_TxConfirmation(TxPduId);
}