// PduR.c
#include "Rte.h"

void PduR_CanIfRxIndication(const Can_MessageType* message) {
    if (message->id == AIRBAG_ID) {
        Rte_Read_AirbagSignal(message->data);
    }
}

void PduR_CanIfTxIndication(const uint8_t* data) {
    CanIf_Transmit(data);
}