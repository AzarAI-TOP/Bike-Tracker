#include "network.h"

NetworkClient::NetworkClient() {}

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

NetworkServer::NetworkServer(uint8_t port, Buzzer& buzzer) {
    server = new AsyncWebServer(port);
    const char index_html[] PROGMEM = R"rawliteral(<!DOCTYPE HTML><html><head><title>Bike Tracker</title><meta name="viewport"content="width=device-width, initial-scale=1"><style>html{font-family:Arial;display:inline-block;text-align:center}h1{font-size:3.0rem}body{max-width:600px;margin:0px auto;padding-bottom:25px}#header{font-size:2.5rem}li{list-style-type:none}li p{display:inline}#buzzer{-webkit-transition-duration:0.4s;transition-duration:0.4s;padding:16px 32px;text-align:center;border-radius:5px;background-color:#4CAF50;color:black;border:2px solid#4CAF50}#buzzer:active{background-color:#aa4810;color:black;border:2px solid#aa4810}</style></head><body><h1>Bike Tracker</h1><p id="header">Info:</p><ul><li><p>SSID:</p>%PLACEHOLDER_SSID%</li><li><p>IP:</p>%PLACEHOLDER_IP%</li><li><p>Signal Strength(RSSI):</p>%PLACEHOLDER_RSSI%</li></ul><p>-----------------------------------------------------</p><button id="buzzer"onclick="onClick_Buzzer()"onmouseup="onRease_Buzzer()">Buzzer</button><script>function onClick_Buzzer(){var xhr=new XMLHttpRequest();xhr.open("GET","/buzzer_on");xhr.send()}function onRease_Buzzer(){var xhr=new XMLHttpRequest();xhr.open("GET","/buzzer_off");xhr.send()}</script></body></html>)rawliteral";

    server->on("/", HTTP_GET, [index_html](AsyncWebServerRequest *request) {
        request->send_P(200, String("text/html"), index_html, processer);
    });

    server->on("/buzzer_on", HTTP_GET, [index_html, &buzzer](AsyncWebServerRequest *request) {
        buzzer.on(3000);
        Serial.println("Buzzer On");
        request->send(200, "text/plain", "OK");
    });

    server->on("/buzzer_off", HTTP_GET, [index_html, &buzzer](AsyncWebServerRequest *request) {
        buzzer.off();
        Serial.println("Buzzer Off");
        request->send(200, "text/plain", "OK");
    });
    server->begin();
}

NetworkServer::~NetworkServer(void) {
    delete server;
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

NetworkClient::~NetworkClient(void) {
    http.end();
}


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