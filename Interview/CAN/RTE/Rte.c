// Rte.c
#include "Application.h"
#include "Dem.h"

void Rte_Read_AirbagSignal(const uint8_t* data) {
    uint8_t crc = CalculateCRC(data, 8);
    if (crc == data[7]) {
        App_ProcessAirbagSignal(data);
    } else {
        Dem_ReportError(DEM_EVENT_ID_CRC_ERROR);
    }
}

void Rte_Send_TorqueData(const uint8_t* data) {
    PduR_CanIfTxIndication(data);
}