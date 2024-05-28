#include <Arduino.h>
#include "network.h"
#include "serial.h"
#include "buzzer.h"
#include "gps.h"
#include "timer.h"

// buzzer instance
#define BUZZER_PORT 10

// wifi client instance
#define SSID "AzarAI"
#define PASSWD "12345678"

// server info
#define SERVER_URL_BASE "http://192.168.128.194:8000/Bike_Tracker/" // 更改IP地址和端口
#define SERVER_URL_BUZZER SERVER_URL_BASE "getBuzzerStatus/"
#define SERVER_URL_RECORD SERVER_URL_BASE "getRecordFlag/"
#define SERVER_URL_GPS SERVER_URL_BASE "updateData/?"
#define SERVER_PORT 8000

// variables for seting up LEDC
const int ledcChannel = 0;
const int ledcFrequency = 5000;
const int dutyCycle = 128; // Duty cycle, ranging from 0 to 255

// some global varialble
Buzzer buzzer;
NetworkClient nclient;
GPS gps;

void setup() {
    // Initialize LEDC Channel
    ledcSetup(ledcChannel, ledcFrequency, 8); // 8 bit resolution
    ledcAttachPin(LED_BUILTIN, ledcChannel); // Attach the LEDC channel to the built-in LED
    ledcWrite(ledcChannel, dutyCycle);  // Set the duty cycle

    // start Serial
    Serial_Init(115200);
    Serial.printf("Serial Connected.\n\nProgram Start.\n\n");

    // start buzzer
    Serial.println("\tConnecting Buzzer.");
    buzzer.Buzzer_Init(BUZZER_PORT);
    Serial.println("\t\tBuzzer Connected.");

    // start network
    Serial.println("\tConnecting Network.");
    nclient.NetworkClient_Init(SSID, PASSWD);
    Serial.println("\t\tNetwork Connected.");

    // NetworkServer nserver(80, buzzer);
    // wait for the GPS connecting
    Serial.printf("\tConnecting to GPS");
    gps.GPS_Init(2, 3, GPS_BAUD);
    while(!gps.GPS_Available()) {
        Serial.printf(".");
        delay(1000);
    }
    Serial.printf("\n\t\tConnection Success!\n");
    buzzer.beep(3000, 100);

    // setup scheduled task
    Serial.println("\tSetup scheduled tasks.");
    // setup timer 0
    setupTimer0(60*1000000); // 60s = 60,000,000us
    // setup timer 1
    setupTimer0(1*1000000); //  1s =  1,000,000us
}

void sendGPSData(void) {
    // get gps info
    GPS_Data data = gps.GPS_GetData();
    // parse gps data and prepare url
    String url(SERVER_URL_GPS);
    url += "latitude=" + urlEncode(String(data.latitude)) + "&";
    url += "longitude=" + urlEncode(String(data.longitude)) + "&";
    url += "speed=" + urlEncode(String(data.speed));
    // send data
    String response = nclient.Get(url.c_str());
    Serial.printf("\tSent location data to server - [%s]\n", response.c_str());
}

void loop() {
    // get gps info
    GPS_Data data = gps.GPS_GetData();

    // executing scheduled task
    if (timer0Flag) {
        timer0Flag = false;
        sendGPSData();
    }

    if (timer1Flag) {
        timer1Flag = false;

        // get status of buzzer
        String content = nclient.Get(SERVER_URL_BUZZER);
        if (content == "True") {
            buzzer.on(3000);
        } else {
            buzzer.off();
        }

        // get status of record_flag
        String record_flag = nclient.Get(SERVER_URL_RECORD);
        if (record_flag == "True") {
            Serial.print("Flag = True ");
            sendGPSData();
        } else {
            Serial.print("Flag = False");
        }

        // print current gps info
        Serial.printf("\tlat = %.4f lon = %.4f\n", data.latitude, data.longitude);
    }
}

