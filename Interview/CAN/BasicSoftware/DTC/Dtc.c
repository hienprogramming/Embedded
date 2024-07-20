// Dtc.c
#include "Dtc.h"
#include <stdio.h> // Chỉ dùng cho mục đích debug

void Dtc_SetDTC(Dtc_CodeType code) {
    // Giả lập thiết lập mã lỗi
    if (code == DTC_CODE_AIRBAG_ERROR) {
        printf("DTC Airbag Error Set\n");
    }
    // Thêm xử lý cho các mã lỗi khác nếu cần
}

void Dtc_ClearDTC(Dtc_CodeType code) {
    // Giả lập xóa mã lỗi
    if (code == DTC_CODE_AIRBAG_ERROR) {
        printf("DTC Airbag Error Cleared\n");
    }
    // Thêm xử lý cho các mã lỗi khác nếu cần
}