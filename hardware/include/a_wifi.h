#ifndef A_WIFI_H
#define A_WIFI_H

// import Arduino ESP32C3 WiFi Library
#include <WiFi.h>

// wifi client instance;
extern WiFiClient client;

// set up wifi
bool WIFI_Init(const char *ssid, const char *password);
void WIFI_printStatus(void);

// connect to server
void WIFI_HTTPRequest(const char *url, const uint16_t port);
bool WIFI_HTTPConnected(void);
bool WIFI_HTTPRead(void);
void WIFI_HTTPClose(void);

#endif