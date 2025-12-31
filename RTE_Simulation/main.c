#include <stdio.h>
#include <stdint.h>
#include "LightControl_SWC.h"

int main()
{
    // TH1 sw button turn of -> the light is turn off  電気を消すーけす
    printf("--------TESTCASE1--------");
    Sim_Hardware_SwitchState = LIGHT_SWITCH_OFF;
    Sim_Hardware_BatteryVoltage = BATTERY_ON;
    Runnable_MainControl(); // Simulation for OS calling
    
    // TH2 sw button turn on, battery is not enough (turn off) -> the light is turn off
    printf("\n--------TESTCASE2--------");
    Sim_Hardware_SwitchState = LIGHT_SWITCH_ON;
    Sim_Hardware_BatteryVoltage = BATTERY_OFF;
    Runnable_MainControl(); // Simulation for OS calling
    
    // TH3 sw button turn on, battery is turn on -> the light is turn on
    printf("\n--------TESTCASE3--------");
    Sim_Hardware_SwitchState = LIGHT_SWITCH_ON;
    Sim_Hardware_BatteryVoltage = BATTERY_ON;
    Runnable_MainControl(); // Simulation for OS calling
}