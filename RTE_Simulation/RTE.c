#include <stdio.h>
#include <stdint.h>
#include "LightControl_SWC.h"

boolean Sim_Hardware_SwitchState = LIGHT_SWITCH_OFF;
uint8 Sim_Hardware_BatteryVoltage = BATTERY_OFF;
boolean Sim_Hardware_LightBulb = FALSE;

Std_ReturnType Rte_Read_R_LightSwitch_Status(uint8 *data){
    *data = Sim_Hardware_SwitchState;
    return RTE_E_OK;
}

Std_ReturnType Rte_Call_R_BatteryService_GetStatus(uint8 *voltageStatus)
{
    printf("[RTE CALL] -> Check Battery Service!!!!\n");
    *voltageStatus = Sim_Hardware_BatteryVoltage;
    return RTE_E_OK;
}

Std_ReturnType Rte_Write_P_LightActuator_Command(boolean Status_Lighting)
{
    Sim_Hardware_LightBulb = Status_Lighting;
    if (Sim_Hardware_LightBulb == TRUE)
    {
        printf("[STATUS OF LIGHT INFOR] Turn ON");
    }
    else{
        printf("[STATUS OF LIGHT INFOR] Turn OFF");
    }
    return RTE_E_OK;
}

