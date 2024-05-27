#ifndef BUZZER_H
#define BUZZER_H

#include <Arduino.h>

class Buzzer
{
private:
    uint8_t buzzer_pin;
public:
    Buzzer();
    void Buzzer_Init(uint8_t pin);
    ~Buzzer();

    void beep(int frequency, int milleseconds);
    void on(int frequency);
    void off();
};

#endif