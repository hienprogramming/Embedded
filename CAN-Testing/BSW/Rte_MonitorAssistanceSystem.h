#ifndef RTE_MONITORASSISTANCESYSTEM_H
#define RTE_MONITORASSISTANCESYSTEM_H

#include "Std_Types.h"

// RTE Read functions
extern boolean Rte_Read_MotorStatus_Fault(void);
extern float Rte_Read_SteeringAngle_Value(void);
extern float Rte_Read_VehicleSpeed_Value(void);

// RTE Write functions
extern Std_ReturnType Rte_Write_WarningLight_Status(boolean status);

// RTE Call functions
extern Std_ReturnType Rte_Call_DiagnosticLog_LogEvent(uint16 eventId);
extern Std_ReturnType Rte_Call_SteeringControl_LimitAngle(float maxAngle);
extern Std_ReturnType Rte_Call_SpeedControl_LimitSpeed(float maxSpeed);

// Constants
#define DIAGNOSTIC_EVENT_WARNING_LIGHT_ON 0x0001
#define MAX_STEERING_ANGLE 45.0f
#define MAX_VEHICLE_SPEED 200.0f

// Function prototypes
void MonitorAssistanceSystem_Init(void);
void MonitorAssistanceSystem_MainFunction(void);

#endif // RTE_MONITORASSISTANCESYSTEM_H