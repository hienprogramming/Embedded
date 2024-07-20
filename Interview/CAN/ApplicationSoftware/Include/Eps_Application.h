// Eps_Application.h
#ifndef EPS_APPLICATION_H_
#define EPS_APPLICATION_H_

void Eps_ReceiveAirbagSignal(void);
void Eps_TransmitAirbagSignal(uint8_t* data, uint8_t length);
void Eps_AdjustTorqueSupport(void);

#endif // EPS_APPLICATION_H_