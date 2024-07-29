#ifndef RTE_EVENTLOGGER_H
#define RTE_EVENTLOGGER_H

#include "Std_Types.h"

typedef struct {
    uint16 EventId;
    char Data[256];
} EventType;

typedef struct {
    EventType Events[10];
    uint8 Size;
} EventLoggerType;

void Rte_Write_EventLogger_LogEvent(uint16 EventId, const char* Data);
void Rte_Read_EventLogger_GetEvents(EventLoggerType* Logger);

#endif // RTE_EVENTLOGGER_H
