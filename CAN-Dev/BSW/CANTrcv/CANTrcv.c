/*
This file contains the definition of CAN initialization and handling functions.

MX_CAN1_Init: Initialize CAN1 with parameters like Prescaler, Mode, Time Segments, etc.
CAN_FilterConfig: Configure filter for CAN to receive messages.
CAN_Transmit: Transmit CAN data.
CAN_Receive: Receive CAN data.
*/
#include "CANTrcv.h"

CAN_HandleTypeDef hcan1;

void MX_CAN1_Init(void) {
    hcan1.Instance = CAN1;
    hcan1.Init.Prescaler = 16;
    hcan1.Init.Mode = CAN_MODE_NORMAL;
    hcan1.Init.SyncJumpWidth = CAN_SJW_1TQ;
    hcan1.Init.TimeSeg1 = CAN_BS1_1TQ;
    hcan1.Init.TimeSeg2 = CAN_BS2_1TQ;
    hcan1.Init.TimeTriggeredMode = DISABLE;
    hcan1.Init.AutoBusOff = DISABLE;
    hcan1.Init.AutoWakeUp = DISABLE;
    hcan1.Init.AutoRetransmission = DISABLE;
    hcan1.Init.ReceiveFifoLocked = DISABLE;
    hcan1.Init.TransmitFifoPriority = DISABLE;
    if (HAL_CAN_Init(&hcan1) != HAL_OK) {
        // Initialization Error
        Error_Handler();
    }
    CAN_FilterConfig();
}

void CAN_FilterConfig(void) {
    CAN_FilterTypeDef filterConfig;
    filterConfig.FilterActivation = ENABLE;
    filterConfig.FilterBank = 0;
    filterConfig.FilterFIFOAssignment = CAN_FILTER_FIFO0;
    filterConfig.FilterIdHigh = 0x0000;
    filterConfig.FilterIdLow = 0x0000;
    filterConfig.FilterMaskIdHigh = 0x0000;
    filterConfig.FilterMaskIdLow = 0x0000;
    filterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
    filterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
    if (HAL_CAN_ConfigFilter(&hcan1, &filterConfig) != HAL_OK) {
        // Filter configuration Error
        Error_Handler();
    }
}

void CAN_Transmit(uint8_t* data, uint8_t length) {
    CAN_TxHeaderTypeDef txHeader;
    uint32_t txMailbox;

    txHeader.DLC = length;
    txHeader.StdId = 0x321;
    txHeader.IDE = CAN_ID_STD;
    txHeader.RTR = CAN_RTR_DATA;
    if (HAL_CAN_AddTxMessage(&hcan1, &txHeader, data, &txMailbox) != HAL_OK) {
        // Transmission request Error
        Error_Handler();
    }
}

void CAN_Receive(uint8_t* data, uint8_t* length) {
    CAN_RxHeaderTypeDef rxHeader;
    if (HAL_CAN_GetRxMessage(&hcan1, CAN_RX_FIFO0, &rxHeader, data) != HAL_OK) {
        // Reception Error
        Error_Handler();
    }
    *length = rxHeader.DLC;
}