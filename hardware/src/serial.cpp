#include "serial.h"


void Serial_Init(unsigned long speed) {
    Serial.begin(speed);
    while (!Serial) {
        delay(100);
    }
}