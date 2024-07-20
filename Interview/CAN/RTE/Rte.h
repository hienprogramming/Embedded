// Rte.h
#ifndef RTE_H
#define RTE_H

#include <stdint.h>

void Rte_Read_AirbagSignal(const uint8_t* data);
void Rte_Send_TorqueData(const uint8_t* data);

#endif // RTE_H