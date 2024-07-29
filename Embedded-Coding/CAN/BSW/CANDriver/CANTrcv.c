// CANTrcv.c
#include "stm32f4xx_hal.h"
#include "CanIf.h"

CAN_HandleTypeDef hcan;

void CAN_Init(void) {
    // Initialize CAN peripheral
    hcan.Instance = CAN1;
    hcan.Init.Prescaler = 16;
    hcan.Init.Mode = CAN_MODE_NORMAL;
    hcan.Init.SyncJumpWidth = CAN_SJW_1TQ;
    hcan.Init.TimeSeg1 = CAN_BS1_1TQ;
    hcan.Init.TimeSeg2 = CAN_BS2_1TQ;
    hcan.Init.TimeTriggeredMode = DISABLE;
    hcan.Init.AutoBusOff = DISABLE;
    hcan.Init.AutoWakeUp = DISABLE;
    hcan.Init.AutoRetransmission = DISABLE;
    hcan.Init.ReceiveFifoLocked = DISABLE;
    hcan.Init.TransmitFifoPriority = DISABLE;
    HAL_CAN_Init(&hcan);
}

void CAN_ReceiveMessage(void) {
    CAN_RxHeaderTypeDef rxHeader;
    uint8_t data[8];
    
    if (HAL_CAN_GetRxMessage(&hcan, CAN_RX_FIFO0, &rxHeader, data) == HAL_OK) {
        Can_MessageType message = {rxHeader.StdId, {0}};
        memcpy(message.data, data, 8);
        CanIf_RxIndication(&message);
    }
}

void CAN_TransmitMessage(const uint8_t* data) {
    CAN_TxHeaderTypeDef txHeader;
    uint32_t txMailbox;

    txHeader.StdId = 0x123; // Example ID
    txHeader.IDE = CAN_ID_STD;
    txHeader.RTR = CAN_RTR_DATA;
    txHeader.DLC = 8;
    HAL_CAN_AddTxMessage(&hcan, &txHeader, (uint8_t*)data, &txMailbox);
}