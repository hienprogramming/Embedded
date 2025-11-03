#include <stdio.h>
#include "App_SWC.h"
#include "Mcal_Can.h"

int main() {
    printf("--- Starting AUTOSAR ComStack Simulation ---\n");
    
    int loop_count = 0;
    while(loop_count < 3) {
        printf("\n\n<<<<<<<<<<<< Simulation Loop %d >>>>>>>>>>>>\n", loop_count + 1);

        // 1. Simulate TX flow (App -> Bus)
        // SW-C task is triggered to send data
        App_Task_Tx();

        // 2. Simulate RX flow (Bus -> App)
        // Simulate receiving a CAN frame from bus
        Mcal_Can_SimulateRx();

        // 3. After data has been processed by BSW layers (in Mcal_Can_SimulateRx function)
        // SW-C task is triggered to read and process new data
        App_Task_Rx();
        
        loop_count++;
    }

    printf("\n--- End of Simulation ---\n");
    return 0;
}
