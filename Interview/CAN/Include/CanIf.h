// CanIf.h
#ifndef CANIF_H_
#define CANIF_H_

#include <stdint.h>
#include "Crc.h"
#include "BitError.h"

#define CAN_RX_ID 0x123
#define CAN_TX_ID 0x321

typedef struct {
    uint8_t* SduDataPtr;
    uint8_t SduLength;
} PduInfoType;

Std_ReturnType CanIf_Receive(uint32_t canId, PduInfoType* pduInfo);
Std_ReturnType CanIf_Transmit(uint32_t canId, const PduInfoType* pduInfo);

#endif // CANIF_H_