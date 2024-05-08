#include <Arduino.h>
#include "network.h"
#include "serial.h"

// the info of WiFi
const char *ssid = "AzarAI";
const char *password = "12345678";

// the address of Server
const char *server = "ifconfig.me";
// const char *server = "azarai.top";
const uint16_t port = 80;

// Network Instance
HTTPClient http;
WiFiClient client;

void setup() {
    // start Serial
    Serial_Init(115200);
    // start WiFi
    // WIFI_Init(ssid, password);
    // WIFI_printStatus();

    // String response = HTTP_Get(server, port, String("/ip"));
    // Serial.printf("Reponse: %s\n", response.c_str());
}

void loop() {
// write your code here
}