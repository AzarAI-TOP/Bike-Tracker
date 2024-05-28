#include "gps.h"

GPS::GPS() {}

void GPS::GPS_Init(uint8_t rxPin, uint8_t txPin, unsigned long baud) {
    // begin the serial connected to GPS module
    gps_serial.begin(baud, SERIAL_8N1, rxPin, txPin);
}

GPS::~GPS(void) {
    gps_serial.end();
}

bool GPS::GPS_Available(void) {
    return gps_serial.available() > 0;
}

int GPS::GPS_Read(void) {
    return gps_serial.read();
}

void GPS::GPS_Parse(void) {
    // read until a valid sentence
    // gps_serial.flush();
    while(GPS_Available() && !gps_parser.encode(GPS_Read())) ;

}

bool GPS::GPS_IsChangedLocation(void) {
    return gps_parser.location.isUpdated();
}

GPS_Data GPS::GPS_GetData(void) {
    do {
        GPS_Parse();
    } while (GPS_IsChangedLocation());

    // parse the gps info into structure and return it
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