#include <stdio.h>
#include "diag.h"

void ECU_ReceiveDiagMsg(const char *msg)
{
    printf("[ECU] Logging fault: %s\n", msg);
}


int main(void)
{
    /* Khởi tạo database lỗi */
    Diag_RegisterError(ERR_ENGINE, "EngineError");
    Diag_RegisterError(ERR_OVERHEAT,"Overheat");
    Diag_RegisterError(ERR_SENSOR, "SensorFault");

    /* Đăng ký subscriber cho từng lỗi */
    Diag_RegisterSubscriber(ERR_ENGINE, "Lamp",  Lamp_ReceiveDiagMsg);
    Diag_RegisterSubscriber(ERR_ENGINE,  "Meter", Meter_ReceiveDiagMsg);
    Diag_RegisterSubscriber(ERR_OVERHEAT,"ECU",   ECU_ReceiveDiagMsg);
    Diag_RegisterSubscriber(ERR_ENGINE,"Brake",   Brake_ReceiveDiagMsg);

    /* Khi lỗi Engine xảy ra -> chỉ Lamp + Meter + Brake (Khách hàng yêu cầu mở rộng) được trigger */
    Diag_HandleError(ERR_ENGINE);

    /* Khi lỗi Overheat xảy ra -> chỉ ECU nhận */
    Diag_HandleError(ERR_OVERHEAT);

    return 0;
}
