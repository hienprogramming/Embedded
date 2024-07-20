// Dcm.c
#include "Rte.h"
#include "Dem.h"
#include "NvM.h"

static uint16_t storedDTCs[10]; // Example storage for DTCs
static uint8_t dtcCount = 0;

void Dcm_MainFunction(void) {
    // Function to handle diagnostics communication (placeholder implementation)
}

void Dcm_StoreDTC(uint16_t eventId) {
    if (dtcCount < 10) {
        storedDTCs[dtcCount++] = eventId;
        NvM_WriteDTC(eventId);
    }
}