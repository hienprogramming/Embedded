#include <stdio.h>
#include "App_SWC.h"
#include "Rte.h"

/**
 * @brief Tác vụ tuần hoàn của SW-C để gửi dữ liệu.
 */
void App_Task_Tx() {
    static uint16 engine_speed = 4000; // Simulated engine speed value (rpm)
    printf("\n--- [APP] TX Task ---\n");
    printf("[APP] Sending EngineSpeed = %d\n", engine_speed);
    
    // Application calls RTE to send signal
    Rte_Write_Signal_EngineSpeed(engine_speed);

    engine_speed += 50; // Increase value for next transmission
    if (engine_speed > 5000) {
        engine_speed = 4000;
    }
}

/**
 * @brief Tác vụ tuần hoàn của SW-C để xử lý dữ liệu nhận được.
 */
void App_Task_Rx() {
    uint16 vehicle_speed;
    printf("\n--- [APP] RX Task ---\n");
    
    // Application calls RTE to read signal value
    Rte_Read_Signal_VehicleSpeed(&vehicle_speed);
    
    printf("[APP] Read VehicleSpeed = %d km/h\n", vehicle_speed);
    // ... Add processing logic for this value here ...
}
