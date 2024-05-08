#include "network.h"

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
    Serial.println("\n\tConnection Success!");

    return true;
}

void WIFI_printStatus(void) {
    // print the SSID of the network you're attached to:
    Serial.print("SSID: ");
    Serial.println(WiFi.SSID());

    // print your WiFi shield's IP address:
    IPAddress ip = WiFi.localIP();
    Serial.print("\tIP Address: ");
    Serial.println(ip);

    // print the received signal strength:
    long rssi = WiFi.RSSI();
    Serial.print("\tsignal strength (RSSI):");
    Serial.print(rssi);
    Serial.println(" dBm");
}

String HTTP_Get(const char *host, uint16_t port, String uri) {
    Serial.println("Send GET request");
    http.begin(client, host, port, uri, true);
    int httpCode = http.GET();
    if (httpCode > 0) {
        if (httpCode == HTTP_CODE_OK) {
            Serial.println("\tGot the response from server");
            String text = http.getString();
            Serial.printf("\tdata = %s\n", text.c_str());
            return text;
        } else {
            Serial.printf("\tError: bad request with httpCode<%d>\n", httpCode);
        }

    } else {
        Serial.println("\tError: httpCode < 0");
    }
}

void HTTP_Close(void) {
    http.end();
}


