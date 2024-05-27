#include <Arduino.h>
#include "network.h"
#include "serial.h"
#include "buzzer.h"
#include "gps.h"

// buzzer instance
#define BUZZER_PORT 10

// wifi client instance
#define SSID "AzarAI"
#define PASSWD "12345678"

// server info
#define SERVER_URL_BUZZER "http://192.168.128.152:8000/Bike_Tracker/getBuzzerStatus/"
#define SERVER_URL_RECORD "http://192.168.128.152:8000/Bike_Tracker/getRecordFlag/"
#define SERVER_URL_GPS "http://192.168.128.152:8000/Bike_Tracker/updateData/?"
#define SERVER_PORT 8000


// wifi server instance
// #define SERVER_PORT 80

// gps instance
#define GPS_BAUD 38400

Buzzer buzzer;
NetworkClient nclient;
GPS gps;

void setup() {
    // start Serial
    Serial_Init(115200);
    Serial.printf("Serial Connected.\n\nProgram Start.\n\n");

    // start buzzer
    Serial.println("Connecting Buzzer.");
    buzzer.Buzzer_Init(BUZZER_PORT);
    Serial.println("\tBuzzer Connected.");

    // start network
    Serial.println("Connecting Network.");
    nclient.NetworkClient_Init(SSID, PASSWD);
    Serial.print("\tNetwork Connected.");

    // NetworkServer nserver(80, buzzer);
    gps.GPS_Init(2, 3, GPS_BAUD);
    // wait for the GPS connecting
    Serial.printf("Connecting to GPS");
    while(!gps.GPS_Available()) {
        Serial.printf(".");
        delay(1000);
    }
    Serial.printf("\n\tConnection Success!\n");
    buzzer.beep(3000, 100);
}

void loop() {
    // get gps info
    gps.GPS_Parse();
    GPS_Data data = gps.GPS_GetData();

    // get status of buzzer
    String content = nclient.Get(SERVER_URL_BUZZER);
    if (content == "True") {
        buzzer.on(3000);
    } else {
        buzzer.off();
    }

    // get status of flag
    String flag = nclient.Get(SERVER_URL_RECORD);
    if (flag == "True") {
        Serial.print("Flag = True");

        String url(SERVER_URL_GPS);
        url += "latitude=" + urlEncode(String(data.latitude)) + "&";
        url += "longitude=" + urlEncode(String(data.longitude)) + "&";
        url += "speed=" + urlEncode(String(data.speed));

        String response = nclient.Get(url.c_str());
        Serial.println(response);

    } else {
        Serial.print("Flag = False");
    }
    // print current gps info
    Serial.printf("\tlat = %.4f lon = %.4f\n", data.latitude, data.longitude);
    delay(500);
}