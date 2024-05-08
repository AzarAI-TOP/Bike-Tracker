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


void WIFI_HTTPRequest(const char *url, const uint16_t port) {
    // print status
    Serial.print("Connect to server - <");
    Serial.print(url);
    Serial.print(":");
    Serial.print(port);
    Serial.println(">");

    // request
    if (client.connect(url, port)) {
        Serial.println("\tConnected to server.");
        // start send request to server
        client.println("GET / HTTP/1.1");
        client.printf("Host: %s\n", url);
        client.println("Connection: close");
        client.println();
    } else {
        Serial.println("\tFailed to connect to server.");
    }
}


bool WIFI_HTTPConnected(void) {
    return client.connected();
}

bool WIFI_HTTPRead(void) {
    Serial.println("Reading data from server.");
    if (client.connected()) {
        // test whether the client is timeout
        unsigned long timeout = millis();
        Serial.print("\tWaiting for data");
        while(client.available() == 0){
            Serial.print(".");
            if(millis() - timeout > 5000){
            Serial.println("\n\tClient Timeout !");
            client.stop();
            return false;
            }
        }
        Serial.println();

        // read data
        Serial.print("\tdata: ");
        // read data
        while(client.available()) {
            String line = client.readStringUntil('\n');
            line.replace("\r", "\\r");
            Serial.println(line);
        }
        return true;
    } else {
        Serial.println("\tClient is not connected.");
        return false;
    }
}

void WIFI_HTTPClose(void) {
    client.stop();
}
