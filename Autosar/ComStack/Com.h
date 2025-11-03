#ifndef COM_H
#define COM_H

#include "Mcal_Can.h"

// Khai báo hàm
void Com_SendSignal_EngineSpeed(uint16 signal_data);
void Com_ReceiveSignal_VehicleSpeed(uint16* signal_data);
void Com_RxIndication(uint16 RxPduId, const PduInfoType* PduInfoPtr);
void Com_TxConfirmation(uint16 TxPduId);

#endif // COM_H
