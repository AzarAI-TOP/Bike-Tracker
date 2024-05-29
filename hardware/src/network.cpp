#include "network.h"

NetworkClient::NetworkClient() : ssid(nullptr), port(0), client(), http() {}

NetworkClient::~NetworkClient() {
    http.end();
    // 其他资源释放
}

void NetworkClient::initialize(const char *ssid, const char *password, uint8_t port) {
    this->ssid = ssid;
    this->port = port;

    WiFi.mode(WIFI_MODE_STA);
    WiFi.begin(ssid, password);

    Serial.printf("\tConnecting to <%s>", ssid);
    unsigned long startTime = millis();
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);

        if (millis() - startTime > TIMEOUTTIME) {
            Serial.println("Failed to connect to WiFi");
            // 这里可以添加重试逻辑或异常处理
        }
    }
    Serial.println("Connected");
}

void NetworkClient::printStatus() {
    static String cachedSSID = WiFi.SSID();
    static String cachedIP = WiFi.localIP().toString();
    static long cachedRSSI = WiFi.RSSI();

    // 如果 WiFi.SSID() 等的值发生了变化，更新缓存
    if (WiFi.SSID() != cachedSSID) {
        cachedSSID = WiFi.SSID();
    }
    if (WiFi.localIP().toString() != cachedIP) {
        cachedIP = WiFi.localIP().toString();
    }
    if (WiFi.RSSI() != cachedRSSI) {
        cachedRSSI = WiFi.RSSI();
    }

    Serial.printf("\tSSID: %s\n", cachedSSID);
    Serial.printf("\tIP Address: %s\n", cachedIP);
    Serial.printf("\tsignal strength (RSSI): %ld dBm\n", cachedRSSI);
}

String NetworkClient::get(const char *url) {
    http.begin(client, url);
    int httpCode = http.GET();
    if (httpCode > 0) {
        if (httpCode == HTTP_CODE_OK) {
            String text = http.getString();
            return text;
        } else {
            Serial.printf("Error: bad request with httpCode<%d>\n", httpCode);
        }
    } else {
        Serial.printf("Error: unable to connect to server\n");
    }
    return String();
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