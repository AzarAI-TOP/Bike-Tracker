#ifndef BUZZER_H
#define BUZZER_H

#include <Arduino.h>

#define BUZZER_Port 7

void Buzzer_Init(void);
void Buzzer_Beep(int frequency, int milleseconds);
void Buzzer_On(int frequency);
void Buzzer_Off(void);

#endif