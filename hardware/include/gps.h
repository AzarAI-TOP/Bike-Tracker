#ifndef GPS_H
#define GPS_H

#include <Arduino.h>
#include <TinyGPSPlus.h>

#define GPS_BAUD 38400

struct GPS_Data {
    // date data
    uint16_t year;
    uint8_t month;
    uint8_t day;
    // time data
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
    // location data
    double longitude;
    double latitude;
    // speed data
    double speed;
};


class GPS {
private:
    TinyGPSPlus gps_parser;
    HardwareSerial gps_serial = Serial1;

public:
    GPS();
    void GPS_Init(uint8_t rxPin, uint8_t txPin, unsigned long baud);
    ~GPS(void);

    bool GPS_Available(void);
    int GPS_Read(void);
    void GPS_Parse(void);
    bool GPS_IsChangedLocation(void) const;
    GPS_Data GPS_GetData(void);

};

#endif