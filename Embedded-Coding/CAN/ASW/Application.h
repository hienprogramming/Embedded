// Application.h
#ifndef APPLICATION_H
#define APPLICATION_H

#include <stdint.h>

void App_ProcessAirbagSignal(const uint8_t* data);
void ReduceTorqueSupport(void);
void NormalTorqueSupport(void);
uint8_t GetCurrentTorque(void);
uint8_t CalculateCRC(const uint8_t* data, uint8_t length);

#endif // APPLICATION_H