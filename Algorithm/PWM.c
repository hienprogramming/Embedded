#include<Aduino.h>

const int pin_PWM = 9;
int duty_Cycles = 80;

void setup()
{
    pinMode(pin_PWM, OUTPUT);
}

void loop()
{
    Pusle = (duty_Cycles * 255) / 100;
    WriteAnalog(pin_PWM, Pusle);
    delay(100);
}