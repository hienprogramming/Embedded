/*This file declares functions to communicate with the CAN layer below.*/
#ifndef CANIF_H
#define CANIF_H

#include <stdint.h>

void CanIf_Init(void);
void CanIf_Transmit(uint8_t* data, uint8_t length);
void CanIf_Receive(uint8_t* data, uint8_t length);
void CanIf_GetReceivedData(uint8_t* data, uint8_t* length);

#endif // CANIF_H