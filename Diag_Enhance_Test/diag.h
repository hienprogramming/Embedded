#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef enum {
    ERR_ENGINE = 0,
    ERR_OVERHEAT,
    ERR_SENSOR,
    ERR_MAX
} DiagErrorId_t;

typedef void (*DiagNotifyFunc)(const char *errorMsg);

void Lamp_ReceiveDiagMsg(const char *msg);
void Meter_ReceiveDiagMsg(const char *msg);
void ECU_ReceiveDiagMsg(const char *msg);
void Brake_ReceiveDiagMsg(const char *msg);
bool Diag_RegisterError(DiagErrorId_t id, const char *name);
bool Diag_RegisterSubscriber(DiagErrorId_t id, const char *compName, DiagNotifyFunc cb);
void Diag_HandleError(DiagErrorId_t id);