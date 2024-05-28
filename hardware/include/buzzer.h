#ifndef BUZZER_H
#define BUZZER_H

#include <Arduino.h>

#define BUZZER_DEFAULT_FREQ 3000
#define BUZZER_DEFAULT_TIME 1000

class Buzzer
{
private:
    uint8_t buzzer_pin;
public:
    Buzzer();
    ~Buzzer();
    void Buzzer_Init(uint8_t pin);

    void beep(int frequency, int milleseconds);
    void on(int frequency);
    void off();
};

#endif