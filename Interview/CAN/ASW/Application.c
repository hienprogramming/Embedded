// Application.c
#include "Rte.h"
#include "Dem.h"

#define NORMAL_TORQUE 7
#define REDUCED_TORQUE 2
#define MIN_RANGE 0
#define MAX_RANGE 255

static uint8_t currentTorque = NORMAL_TORQUE;

void App_ProcessAirbagSignal(const uint8_t* data) {
    uint8_t airbagSignal = data[0];
    if (airbagSignal < MIN_RANGE || airbagSignal > MAX_RANGE) {
        ReduceTorqueSupport();
        Dem_ReportError(DEM_EVENT_ID_AIRBAG_OUT_OF_RANGE);
    } else {
        NormalTorqueSupport();
    }

    uint8_t torqueData[8] = {currentTorque, 0, 0, 0, 0, 0, 0, CalculateCRC(&currentTorque, 1)};
    Rte_Send_TorqueData(torqueData);
}

void ReduceTorqueSupport(void) {
    currentTorque = REDUCED_TORQUE;
}

void NormalTorqueSupport(void) {
    currentTorque = NORMAL_TORQUE;
}

uint8_t GetCurrentTorque(void) {
    return currentTorque;
}

uint8_t CalculateCRC(const uint8_t* data, uint8_t length) {
    uint8_t crc = 0xFF;
    for (uint8_t i = 0; i < length; ++i) {
        crc ^= data[i];
        for (uint8_t j = 0; j < 8; ++j) {
            if (crc & 0x80) {
                crc = (crc << 1) ^ 0x31;
            } else {
                crc <<= 1;
            }
        }
    }
    return crc;
}