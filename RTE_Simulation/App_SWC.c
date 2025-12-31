#include "LightControl_SWC.h"

void Runnable_MainControl()
{
    boolean switchStatus = 0;
    uint8 BatteryStatus = 0;
    boolean lightCommand = FALSE;
    Std_ReturnType status;

    printf("\n--- Runnable_MainControl START ---\n");
    status = Rte_Read_R_LightSwitch_Status(&switchStatus);
    if (status == RTE_E_OK)
    {
        if (switchStatus == LIGHT_SWITCH_ON)
        {
            Rte_Call_R_BatteryService_GetStatus(&BatteryStatus);
            if (BatteryStatus == BATTERY_ON)
            {
                lightCommand = TRUE;
            }
            else{
                printf("[LOGIC INFO] -> Battery is not enough!, can not turn on the light.\n");
                lightCommand = FALSE;
            }
        }
        else {
            printf("[LOGIC INFO] -> Battery is turn off!");
            lightCommand = FALSE;
        }
    }

    // Send to Port (Sender)
    Rte_Write_P_LightActuator_Command(lightCommand);
    printf("\n--- Runnable_MainControl END ---\n");
}