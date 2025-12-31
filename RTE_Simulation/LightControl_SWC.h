#include <stdio.h>
#include <stdint.h>

typedef uint8_t uint8;
typedef uint8_t boolean;
typedef uint8_t Std_ReturnType;

#define RTE_E_OK   0
#define RTE_E_NOK  1

#define TRUE  1
#define FALSE 0

#define LIGHT_SWITCH_OFF   0x00
#define LIGHT_SWITCH_ON    0x01
#define BATTERY_OFF        0x00
#define BATTERY_ON         0x01

extern boolean Sim_Hardware_SwitchState;
extern uint8 Sim_Hardware_BatteryVoltage;
extern boolean Sim_Hardware_LightBulb;

void Runnable_MainControl();

Std_ReturnType Rte_Read_R_LightSwitch_Status(uint8 *data);
Std_ReturnType Rte_Call_R_BatteryService_GetStatus(uint8 *voltageStatus);
Std_ReturnType Rte_Write_P_LightActuator_Command(boolean Status_Lighting);
