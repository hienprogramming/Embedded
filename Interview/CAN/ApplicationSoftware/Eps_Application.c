// Eps_Application.c
#include "CanIf.h"
#include "Eps_Application.h"
#include "Dem.h"
#include "Dtc.h"
#include <string.h>

#define AIRBAG_DATA_LENGTH 8
#define TORQUE_SUPPORT_NORMAL 100
#define TORQUE_SUPPORT_REDUCED 50

static uint8_t torqueSupport = TORQUE_SUPPORT_NORMAL;

void Eps_ReceiveAirbagSignal(void) {
    uint8_t data[AIRBAG_DATA_LENGTH];
    PduInfoType pduInfo = {
        .SduDataPtr = data,
        .SduLength = AIRBAG_DATA_LENGTH
    };

    Std_ReturnType ret = CanIf_Receive(CAN_RX_ID, &pduInfo);
    if (ret == E_OK) {
        uint8_t airbag_signal = data[0];  // Giả sử tín hiệu airbag nằm ở byte đầu tiên
        // Xử lý tín hiệu airbag
        if (airbag_signal == 0xFF) {  // Giả sử 0xFF là tín hiệu lỗi
            Dem_ReportErrorStatus(DEM_EVENT_ID_AIRBAG_ERROR, DEM_EVENT_STATUS_FAILED);
            Dtc_SetDTC(DTC_CODE_AIRBAG_ERROR);
            Eps_AdjustTorqueSupport();
        } else {
            Dem_ReportErrorStatus(DEM_EVENT_ID_AIRBAG_ERROR, DEM_EVENT_STATUS_PASSED);
            Dtc_ClearDTC(DTC_CODE_AIRBAG_ERROR);
        }
    } else {
        // Ghi nhận lỗi khi nhận dữ liệu CAN
    }
}

void Eps_TransmitAirbagSignal(uint8_t* data, uint8_t length) {
    if (length > AIRBAG_DATA_LENGTH - 1) {
        // Dữ liệu quá dài
        return;
    }

    PduInfoType pduInfo = {
        .SduDataPtr = data,
        .SduLength = length + 1  // Thêm 1 byte cho CRC
    };

    Std_ReturnType ret = CanIf_Transmit(CAN_TX_ID, &pduInfo);
    if (ret != E_OK) {
        // Ghi nhận lỗi khi truyền dữ liệu CAN
    }
}

void Eps_AdjustTorqueSupport(void) {
    // Giảm Torque hỗ trợ khi phát hiện lỗi airbag
    torqueSupport = TORQUE_SUPPORT_REDUCED;
    // Thêm logic điều chỉnh torque hỗ trợ cho hệ thống EPS
}