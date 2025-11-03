#include <stdio.h>
#include "Com.h"
#include "PduR.h"

#define PDU_ID_ENGINEDATA 0
#define PDU_ID_VEHICLESPEED 10

// Buffer để lưu trữ dữ liệu cho các PDU
uint8 g_engineDataPduBuffer[8] = {0};
uint16 g_vehicleSpeedSignal = 0; // Biến lưu trữ giá trị signal nhận được

/**
 * @brief Hàm được gọi bởi RTE để ghi một signal.
 * Hàm này sẽ đóng gói signal vào PDU buffer và yêu cầu PduR truyền đi.
 * @param signal_data Dữ liệu của signal (tốc độ động cơ)
 */
void Com_SendSignal_EngineSpeed(uint16 signal_data) {
    printf("[COM] Received EngineSpeed = %d from RTE. Packing into PDU ID %d\n", signal_data, PDU_ID_ENGINEDATA);
    
    // Packing: 2 bytes of signal_data into first 2 bytes of PDU buffer
    // Byte 0: low 8 bits, Byte 1: high 8 bits (Little-Endian)
    g_engineDataPduBuffer[0] = (uint8)(signal_data & 0xFF);
    g_engineDataPduBuffer[1] = (uint8)((signal_data >> 8) & 0xFF);

    PduInfoType txPdu;
    txPdu.SduDataPtr = g_engineDataPduBuffer;
    txPdu.SduLength = 2; // DLC = 2 bytes

    PduR_ComTransmit(PDU_ID_ENGINEDATA, &txPdu);
}

/**
 * @brief Hàm được gọi bởi RTE để đọc một signal.
 * @param signal_data Con trỏ để trả về giá trị signal.
 */
void Com_ReceiveSignal_VehicleSpeed(uint16* signal_data) {
    *signal_data = g_vehicleSpeedSignal;
     printf("[COM] Application reading VehicleSpeed signal. Returning value = %d\n", *signal_data);
}

/**
 * @brief Hàm được gọi bởi PduR khi có PDU được nhận.
 * Hàm này sẽ mở gói (unpack) signal từ PDU và lưu lại.
 */
void Com_RxIndication(uint16 RxPduId, const PduInfoType* PduInfoPtr) {
    if (RxPduId == PDU_ID_VEHICLESPEED) {
        printf("[COM] Received PDU ID %d. Unpacking VehicleSpeed signal.\n", RxPduId);
        // Unpacking: first 2 bytes of PDU into 16-bit signal (Little-Endian)
        g_vehicleSpeedSignal = (uint16)PduInfoPtr->SduDataPtr[0] | ((uint16)PduInfoPtr->SduDataPtr[1] << 8);
        printf("[COM] Unpacked VehicleSpeed = %d\n", g_vehicleSpeedSignal);
    }
}

/**
 * @brief Hàm được gọi bởi PduR khi có xác nhận truyền thành công.
 */
void Com_TxConfirmation(uint16 TxPduId) {
    if (TxPduId == PDU_ID_ENGINEDATA) {
        printf("[COM] Received confirmation (TxConfirmation) for PDU ID %d.\n", TxPduId);
        // Can notify SW-C here if needed
    }
}
