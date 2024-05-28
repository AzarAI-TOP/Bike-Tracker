#include "network.h"

// Class -- NetworkURL
NetworkURL::NetworkURL() {}
NetworkURL::~NetworkURL() {
    params.clear();
}

void NetworkURL::NetworkURL_Init(String host, String port) {
    url = "http://" + host + ":" + port;
}

void NetworkURL::addParam(String key, String value) {
    params.push_back(std::pair<String, String>(key, value));
}

const char* NetworkURL::c_str() {
    // construct base url
    String fullURL = url + "?";
    // append params
    bool first = true;
    for(auto &item:params) {
        if (!first) {
            fullURL += "&";
        }
        fullURL += item.first + "=" + urlEncode(item.second);
        first = false;
    }

    return fullURL.c_str();
}

// Class -- NetworkClient
NetworkClient::NetworkClient() {}
NetworkClient::~NetworkClient(void) {
    http.end();
}

void NetworkClient::NetworkClient_Init(const char *ssid, const char *password) {
    // start WiFi
    WiFi.mode(WIFI_MODE_APSTA);
    WiFi.useStaticBuffers(true);
    WiFi.begin(ssid, password);

    // wait for connecting
    Serial.printf("\tConnecting to <%s>", ssid);
    time_t startTime = millis();
    while (WiFi.status() != WL_CONNECTED) {
        Serial.printf(".");
        delay(500);

        // check if program timeout
        if (millis() - startTime > TIMEOUTTIME) {
            Serial.println("Failed to connect to WiFi");
            ESP.restart();
        }
    }
    Serial.println();
}

void NetworkClient::printStatus(void) {
    // print the SSID of the network you're attached to:
    Serial.printf("\tSSID: %s\n", WiFi.SSID());

    // print your WiFi shield's IP address:
    // IPAddress ip = WiFi.localIP();
    IPv6Address ip = WiFi.localIPv6();
    Serial.printf("\tIP Address: %s\n", ip.toString());

    // print the received signal strength:
    long rssi = WiFi.RSSI();
    Serial.printf("\tsignal strength (RSSI): %ld dBm\n", rssi);
}

String processer(const String& var) {
    if (var == "PLACEHOLDER_SSID") {
        return WiFi.SSID();
    } else if (var == "PLACEHOLDER_IP") {
        return WiFi.localIP().toString();
    } else if (var == "PLACEHOLDER_RSSI") {
        return String(WiFi.RSSI());
    } else {
        return String();
    }
}

String NetworkClient::Get(const char *url) {
    http.begin(url);
    int httpCode = http.GET();
    if (httpCode > 0) {
        if (httpCode == HTTP_CODE_OK) {
            String text = http.getString();
            return text;
        } else {
            Serial.printf("Error: bad request with httpCode<%d>\n", httpCode);
            return String();
        }
    } else {
        return String();
    }
}

// Utilities
String urlEncode(String str) {
    String encodedString = "";
    char c;
    char code0;
    char code1;
    char code2;
    for (int i = 0; i < str.length(); i++) {
        c = str.charAt(i);
        if (c == ' ') {
            encodedString += '+';
        } else if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
            encodedString += c;
        } else {
            code1 = (c & 0xf) + '0';
            if ((c & 0xf) > 9) {
                code1 = (c & 0xf) - 10 + 'A';
            }
            c = (c >> 4) & 0xf;
            code0 = c + '0';
            if (c > 9) {
                code0 = c - 10 + 'A';
            }
            code2 = '\0';
            encodedString += '%';
            encodedString += code0;
            encodedString += code1;
            encodedString+=code2;
        }
    }
    return encodedString;
}