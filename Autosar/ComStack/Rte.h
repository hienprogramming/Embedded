#ifndef RTE_H
#define RTE_H

#include "Com.h" // RTE sẽ gọi trực tiếp COM trong ví dụ này

// Macro để ánh xạ lời gọi RTE tới module COM
// Trong RTE thật, đây là các hàm được генеруються tự động

#define Rte_Write_Signal_EngineSpeed(data) Com_SendSignal_EngineSpeed(data)
#define Rte_Read_Signal_VehicleSpeed(data_ptr) Com_ReceiveSignal_VehicleSpeed(data_ptr)

#endif // RTE_H
