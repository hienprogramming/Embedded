// Dem.c
#include "Dem.h"
#include "NvM.h"
#include "Dcm.h"

void Dem_ReportError(uint16_t eventId) {
    NvM_WriteError(eventId);
    Dcm_StoreDTC(eventId);
}