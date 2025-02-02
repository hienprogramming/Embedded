// CanIf.h
#ifndef CANIF_H
#define CANIF_H

#include "Can_MessageType.h"

void CanIf_RxIndication(const Can_MessageType* message);
void CanIf_Transmit(const uint8_t* data);

#endif // CANIF_H