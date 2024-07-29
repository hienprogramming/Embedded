/*
This file contains function declarations 
and includes needed for CAN configuration and data transmission/reception.
*/

#ifndef CAN_H
#define CAN_H

#include "stm32f4xx_hal.h"

void MX_CAN1_Init(void);
void CAN_FilterConfig(void);
void CAN_Transmit(uint8_t* data, uint8_t length);
void CAN_Receive(uint8_t* data, uint8_t* length);

#endif // CAN_H