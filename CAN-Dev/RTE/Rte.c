/*
Rte_Init: Initialize the BSW layer.
Rte_Transmit: Transmit CAN data via the BSW layer.
Rte_Receive: Receive CAN data via the BSW layer.
Rte_GetReceivedData: Get the data received from the BSW layer.
*/
#include "Rte.h"
#include "CanIf.h"

void Rte_Init(void) {
    CanIf_Init();
}

void Rte_Transmit(uint8_t* data, uint8_t length) {
    CanIf_Transmit(data, length);
}

void Rte_Receive(uint8_t* data, uint8_t length) {
    CanIf_Receive(data, length);
}

void Rte_GetReceivedData(uint8_t* data, uint8_t* length) {
    CanIf_GetReceivedData(data, length);
}