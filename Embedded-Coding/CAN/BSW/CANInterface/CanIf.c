// CanIf.c
#include "PduR.h"

void CanIf_RxIndication(const Can_MessageType* message) {
    PduR_CanIfRxIndication(message);
}

void CanIf_Transmit(const uint8_t* data) {
    CAN_TransmitMessage(data);
}