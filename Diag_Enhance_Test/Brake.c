#include <stdio.h>

// Call back cho Brake component
void Brake_ReceiveDiagMsg(const char *msg)
{
    printf("[Brake] Active to Brake: %s\n", msg);
}
