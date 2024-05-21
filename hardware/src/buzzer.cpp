#include "buzzer.h"

void Buzzer_Init(void) {
    pinMode(BUZZER_Port, OUTPUT);
}

void Buzzer_Beep(int frequency, int milleseconds) {
    tone(BUZZER_Port, frequency, milleseconds);
}

void Buzzer_On(int frequency) {
    tone(BUZZER_Port, frequency);
}

void Buzzer_Off(void) {
    noTone(BUZZER_Port);
}