// Dem.h
#ifndef DEM_H_
#define DEM_H_

#include <stdint.h>

typedef enum {
    DEM_EVENT_ID_AIRBAG_ERROR,
    // Thêm các sự kiện khác nếu cần
} Dem_EventIdType;

typedef enum {
    DEM_EVENT_STATUS_FAILED,
    DEM_EVENT_STATUS_PASSED,
    // Thêm các trạng thái khác nếu cần
} Dem_EventStatusType;

void Dem_ReportErrorStatus(Dem_EventIdType eventId, Dem_EventStatusType status);

#endif // DEM_H_