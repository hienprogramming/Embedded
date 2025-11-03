#ifndef CANIF_H
#define CANIF_H

#include "Mcal_Can.h" // Để sử dụng PduInfoType

// Khai báo hàm
void CanIf_Transmit(uint16 TxPduId, const PduInfoType* PduInfoPtr);
void CanIf_RxIndication(uint16 CanId, const PduInfoType* PduInfoPtr);
void CanIf_TxConfirmation(uint16 TxPduId);

#endif // CANIF_H