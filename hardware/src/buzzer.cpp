#include "buzzer.h"

Buzzer::Buzzer() {}
Buzzer::~Buzzer() {
    noTone(buzzer_pin);
}

void Buzzer::Buzzer_Init(uint8_t pin) {
    buzzer_pin = pin;
    pinMode(buzzer_pin, OUTPUT);
}

void Buzzer::beep(int frequency, int milleseconds) {
    if (frequency <= 0) frequency = BUZZER_DEFAULT_FREQ;
    if (milleseconds <= 0) milleseconds = BUZZER_DEFAULT_TIME;
    tone(buzzer_pin, frequency, milleseconds);
}

void Buzzer::on(int frequency) {
    if (frequency <= 0) frequency = BUZZER_DEFAULT_FREQ;
    tone(buzzer_pin, frequency);
}

void Buzzer::off(void) {
    noTone(buzzer_pin);
}

