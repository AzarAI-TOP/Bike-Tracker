#ifndef NETWORK_H
#define NETWORK_H

// import Arduino ESP32C3 WiFi Library
#include <WiFi.h>
#include <WiFiClient.h>
#include <HTTPClient.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

#include "buzzer.h"

#define TIMEOUTTIME 1000

String urlEncode(String str);

class NetworkClient {
private:
    char *ssid;
    uint8_t port;

    WiFiClient client;
public:
    HTTPClient http;
    NetworkClient();
    void NetworkClient_Init(const char *ssid, const char *password);
    ~NetworkClient(void);

    // set up wifi
    void printStatus(void);

    // network request
    String Get(const char *url);
};

class NetworkServer {
private:
    uint8_t port;
    AsyncWebServer *server;
public:
    NetworkServer(uint8_t port, Buzzer& buzzer);
    ~NetworkServer(void);

};

String processer(const String& var);

#endif