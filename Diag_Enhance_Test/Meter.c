#include <stdio.h>
// Call back for Meter component
void Meter_ReceiveDiagMsg(const char *msg)
{
    printf("[Meter] Displaying: %s\n", msg);
}