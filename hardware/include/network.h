#ifndef NETWORK_H
#define NETWORK_H

#include <WiFi.h>
#include <WiFiClient.h>
#include <HTTPClient.h>

#define TIMEOUTTIME 1000

class NetworkClient {
private:
    const char *ssid;
    uint8_t port;
    WiFiClient client;
    HTTPClient http;

public:
    // Constructor with initialization list
    NetworkClient();
    ~NetworkClient();

    // Set up WiFi
    void initialize(const char *ssid, const char *password, uint8_t port = 80);

    // Print WiFi status
    void printStatus();

    // Network request
    String get(const char *url);

};

// Utilities
String urlEncode(String str);

#endif // NETWORK_H
