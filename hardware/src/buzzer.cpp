#include "buzzer.h"

Buzzer::Buzzer() {}

void Buzzer::Buzzer_Init(uint8_t pin) {
    buzzer_pin = pin;
    pinMode(buzzer_pin, OUTPUT);
}

Buzzer::~Buzzer() {
    noTone(buzzer_pin);
}

void Buzzer_Init(void) {
}

void Buzzer::beep(int frequency, int milleseconds) {
    tone(buzzer_pin, frequency, milleseconds);
}

void Buzzer::on(int frequency) {
    tone(buzzer_pin, frequency);
}

void Buzzer::off(void) {
    noTone(buzzer_pin);
}

