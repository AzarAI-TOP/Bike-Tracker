#include <Arduino.h>
#include "a_wifi.h"
#include "a_serial.h"

// the info of WiFi
const char *ssid = "AzarAI";
const char *password = "12345678";

// the address of Server
// const char *server = "ifconfig.me";
const char *server = "azarai.top";
const uint16_t port = 80;

WiFiClient client;

void setup() {
    // start Serial
    Serial_Init(115200);
    // start WiFi
    WIFI_Init(ssid, password);
    WIFI_printStatus();

    // test for request
    WIFI_HTTPRequest(server, port);
    if (WIFI_HTTPConnected()) {
        WIFI_HTTPRead();
        WIFI_HTTPClose();
    }
}

void loop() {
// write your code here
}