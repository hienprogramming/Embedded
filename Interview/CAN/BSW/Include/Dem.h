// Dem.h
#ifndef DEM_H
#define DEM_H

#define DEM_EVENT_ID_CRC_ERROR 0x01
#define DEM_EVENT_ID_AIRBAG_OUT_OF_RANGE 0x02

void Dem_ReportError(uint16_t eventId);

#endif // DEM_H