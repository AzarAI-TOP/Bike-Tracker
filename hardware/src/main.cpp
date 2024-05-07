#include <Arduino.h>
#include "a_wifi.h"

const char *ssid = "AzarAI";
const char *password = "12345678";

void setup() {
    // start Serial
    Serial.begin(115200);
    // start WiFi
    WIFI_Init(ssid, password);

}

void loop() {
// write your code here
}