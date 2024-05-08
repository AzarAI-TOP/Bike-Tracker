#ifndef NETWORK_H
#define NETWORK_H

// import Arduino ESP32C3 WiFi Library
#include <WiFi.h>
#include <WiFiClient.h>
#include <HTTPClient.h>

// wifi client instance;
extern HTTPClient http;
extern WiFiClient client;

// set up wifi
bool WIFI_Init(const char *ssid, const char *password);
void WIFI_printStatus(void);

// connect to server
String HTTP_Get(const char *host, uint16_t port, String uri);
void HTTP_Close(void);


#endif