#include "gps.h"

GPS::GPS() {}

void GPS::GPS_Init(uint8_t rxPin, uint8_t txPin, unsigned long baud) {
    // begin the serial connected to GPS module
    gps_serial.begin(baud, SERIAL_8N1, rxPin, txPin);
}

GPS::~GPS() {
    if (gps_serial) {
        gps_serial.end();
    }
}

bool GPS::GPS_Available(void) {
    return gps_serial && gps_serial.available() > 0;
}

int GPS::GPS_Read(void) {
    if (GPS_Available()) {
        return gps_serial.read();
    }
    return -1; // or some error value
}

void GPS::GPS_Parse(void) {
    if (GPS_Available()) {
        // Read and parse one character at a time
        char c = GPS_Read();
        gps_parser.encode(c);
    }
}

bool GPS::GPS_IsChangedLocation(void) const {
    return gps_parser.location.isUpdated();
}

GPS_Data GPS::GPS_GetData(void) {
    Serial.print("Getting GPS data.");
    // Parse until the location is updated
    int times = 10;
    while (!GPS_IsChangedLocation() && times) {
        GPS_Parse();
        Serial.print('.');
        delay(500);
        times -= 1;
    }

    // Parse the gps info into structure and return it
    GPS_Data data = {
        .year = gps_parser.date.year(),
        .month = gps_parser.date.month(),
        .day = gps_parser.date.day(),
        .hour = gps_parser.time.hour(),
        .minute = gps_parser.time.minute(),
        .second = gps_parser.time.second(),
        .longitude = gps_parser.location.lng(),
        .latitude = gps_parser.location.lat(),
        .speed = gps_parser.speed.mps()
    };
    return data;
}
