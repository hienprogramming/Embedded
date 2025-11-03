#include <stdio.h>

// Call back cho Lamp component

void Lamp_ReceiveDiagMsg(const char *msg)
{
    printf("[Lamp] Warning light ON: %s\n", msg);
}
