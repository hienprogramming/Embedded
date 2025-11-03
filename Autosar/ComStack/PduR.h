#ifndef PDUR_H
#define PDUR_H

#include "Mcal_Can.h"

// Khai báo hàm
void PduR_ComTransmit(uint16 TxPduId, const PduInfoType* PduInfoPtr);
void PduR_CanIfRxIndication(uint16 RxPduId, const PduInfoType* PduInfoPtr);
void PduR_CanIfTxConfirmation(uint16 TxPduId);

#endif // PDUR_H