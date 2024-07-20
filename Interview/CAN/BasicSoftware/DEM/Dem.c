// Dem.c
#include "Dem.h"
#include <stdio.h> // Chỉ dùng cho mục đích debug

void Dem_ReportErrorStatus(Dem_EventIdType eventId, Dem_EventStatusType status) {
    // Giả lập báo cáo trạng thái lỗi
    if (eventId == DEM_EVENT_ID_AIRBAG_ERROR) {
        if (status == DEM_EVENT_STATUS_FAILED) {
            printf("Airbag Error Reported\n");
        } else {
            printf("Airbag Error Cleared\n");
        }
    }
    // Thêm xử lý cho các sự kiện khác nếu cần
}