/*
Swc_Init: Initialize the RTE class.
Swc_MainFunction: Main function of the application, transmit torque data and process received data.
Swc_HandleReceivedData: Process data received from the RTE class.
*/
#include "Swc.h"
#include "Rte.h"

void Swc_Init(void) {
    Rte_Init();
}

void Swc_MainFunction(void) {
    uint8_t torque = 100; // Example torque value
    uint8_t airbagStatus = 0; // 0: OK, 1: Fault

    // Simulate airbag status check
    if (airbagStatus == 1) {
        torque /= 2; // Reduce torque to half if airbag is faulty
    }

    // Transmit torque value
    Rte_Transmit(&torque, sizeof(torque));

    // Handle received data from RTE
    Swc_HandleReceivedData();
}

void Swc_HandleReceivedData(void) {
    uint8_t receivedData[8];
    uint8_t receivedLength = 0;

    Rte_GetReceivedData(receivedData, &receivedLength);

    if (receivedLength > 0) {
        // Process received data
        printf("Received data: ");
        for (uint8_t i = 0; i < receivedLength; i++) {
            printf("%02X ", receivedData[i]);
        }
        printf("\n");
    }
}