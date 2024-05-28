#ifndef NETWORK_H
#define NETWORK_H

// import Arduino ESP32C3 WiFi Library
#include <WiFi.h>
#include <WiFiClient.h>
#include <HTTPClient.h>
// import STL
#include <vector>
#include <utility>
// import self-made library
#include "buzzer.h"

#define TIMEOUTTIME 1000

String urlEncode(String str);

class NetworkURL {
private:
    String url;
    std::vector<std::pair<String, String>> params;

public:
    NetworkURL();
    ~NetworkURL();

    void NetworkURL_Init(String host, String port);
    void addParam(String key, String value);
    const char* c_str();
};

class NetworkClient {
private:
    char *ssid;
    uint8_t port;

    WiFiClient client;
    HTTPClient http;
public:
    NetworkClient();
    void NetworkClient_Init(const char *ssid, const char *password);
    ~NetworkClient(void);

    // set up wifi
    void printStatus(void);

    // network request
    String Get(const char *url);
};


#endif