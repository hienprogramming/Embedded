// Dtc.h
#ifndef DTC_H_
#define DTC_H_

#include <stdint.h>

typedef enum {
    DTC_CODE_AIRBAG_ERROR = 0x01,
    // Thêm các mã lỗi khác nếu cần
} Dtc_CodeType;

void Dtc_SetDTC(Dtc_CodeType code);
void Dtc_ClearDTC(Dtc_CodeType code);

#endif // DTC_H_