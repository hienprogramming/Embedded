#ifndef RTE_H
#define RTE_H

#include <stdint.h>

void Rte_Init(void);
void Rte_Transmit(uint8_t* data, uint8_t length);
void Rte_Receive(uint8_t* data, uint8_t length);
void Rte_GetReceivedData(uint8_t* data, uint8_t* length);

#endif // RTE_H