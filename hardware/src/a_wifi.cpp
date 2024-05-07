#include "a_wifi.h"

bool WIFI_Init(const char *ssid, const char *password) {
    // start WiFi
    WiFi.mode(WIFI_MODE_STA);
    WiFi.useStaticBuffers(true);
    WiFi.begin(ssid, password);

    // wait for connecting
    Serial.print("Connecting to <");
    Serial.print(ssid);
    Serial.print(">");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConnection Success!");

    return true;
}