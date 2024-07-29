/*
CanIf_Init: Initialize CAN and enable interrupt notification.
CanIf_Transmit: Transmit CAN data.
CanIf_Receive: Receive CAN data and save it to buffer.
CanIf_GetReceivedData: Get received data from buffer.
*/

#include "CanIf.h"
#include "CANTrcv.h"

static uint8_t receivedData[8];
static uint8_t receivedLength = 0;

void CanIf_Init(void) {
    MX_CAN1_Init();
    HAL_CAN_Start(&hcan1);
    HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);
}

void CanIf_Transmit(uint8_t* data, uint8_t length) {
    CAN_Transmit(data, length);
}

void CanIf_Receive(uint8_t* data, uint8_t length) {
    CAN_Receive(data, &length);
    for (uint8_t i = 0; i < length; i++) {
        receivedData[i] = data[i];
    }
    receivedLength = length;
}

void CanIf_GetReceivedData(uint8_t* data, uint8_t* length) {
    *length = receivedLength;
    for (uint8_t i = 0; i < receivedLength; i++) {
        data[i] = receivedData[i];
    }
}