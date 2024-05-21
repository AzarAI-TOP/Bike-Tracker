#include <Arduino.h>
#include <SoftwareSerial.h>
#include <TinyGPSPlus.h>

// SoftwareSerial Serial1(19, 18);
// HardwareSerial Serial1(0);
// TinyGPSPlus gps;

void setup(){
    Serial.begin(115200);
    Serial1.begin(38400, SERIAL_8N1, 2, 3);


    Serial.println("Start.");

    Serial.print("Waiting for the SoftwareSerial available.");
    while (!Serial1.available()) {
        Serial.print(".");
        delay(1000);
    }
    Serial.println("\n\tSerial1 available");
}

void loop(){
    if (Serial1.available() > 0){
        // gps.encode(Serial1.read());
        // if (gps.location.isUpdated()) {
        if (1) {
            // Serial.print("维度=");//Latitude
            // Serial.print(gps.location.lat(), 6);
            // Serial.print("经度 =");//Longitude
            // Serial.println(gps.location.lng(), 6);
            // Serial.print("原始纬度 = ");//Raw latitude
            // Serial.print(gps.location.rawLat().negative ? "-" : "+");
            // Serial.println(gps.location.rawLat().deg);
            // Serial.println(gps.location.rawLat().billionths);
            // Serial.print("原始经度 = ");//Raw longitude
            // Serial.print(gps.location.rawLng().negative ? "-" : "+");
            // Serial.println(gps.location.rawLng().deg);
            // Serial.println(gps.location.rawLng().billionths);
            // Serial.print("原始日期DDMMYY = ");//Raw date DDMMYY
            // Serial.println(gps.date.value());
            // Serial.print("年 = ");//Year
            // Serial.println(gps.date.year());
            // Serial.print("月 = ");//Month
            // Serial.println(gps.date.month());
            // Serial.print("日 = ");//Day
            // Serial.println(gps.date.day());
            // Serial.print("HHMMSCC中的原始时间 = ");//Raw time in HHMMSerial1CC
            // Serial.println(gps.time.value());
            // Serial.print("小时 = ");//Hour
            // Serial.println(gps.time.hour());
            // Serial.print("分钟 = ");//Minute
            // Serial.println(gps.time.minute());
            // Serial.print("秒 = ");//Second
            // Serial.println(gps.time.second());
            // Serial.print("百分之一秒 = ");//Centisecond
            // Serial.println(gps.time.centisecond());
            // Serial.print("原始速度（单位：100ths/knot） = ");//Raw speed in 100ths/knot
            // Serial.println(gps.speed.value());
            // Serial.print("速度（节/小时） = ");//Speed in knots/h
            // Serial.println(gps.speed.knots());
            // Serial.println(gps.speed.mph());
            // Serial.print("速度米/秒 = ");//Speed in m/s
            // Serial.println(gps.speed.mps());
            // Serial.print("速度每小时/公里 = ");//Speed in km/h
            // Serial.println(gps.speed.kmph());
            // Serial.print("原始课程（以度为单位） = ");//Raw course in degrees
            // Serial.println(gps.course.value());
            // Serial.print("Course in degrees = ");//Course in degrees
            // Serial.println(gps.course.deg());
            // Serial.print("原始高度（厘米） = ");//Raw altitude in centimeters
            // Serial.println(gps.altitude.value());
            // Serial.print("海拔高度（米） = ");//Altitude in meters
            // Serial.println(gps.altitude.meters());
            // Serial.print("海拔高度（英里） = ");//Altitude in miles
            // Serial.println(gps.altitude.miles());
            // Serial.print("海拔高度（千米） = ");//Altitude in kilometersSerial.print("维度=");//Latitude
            // Serial.print(gps.location.lat(), 6);
            // Serial.print("经度 =");//Longitude
            // Serial.println(gps.location.lng(), 6);
            // Serial.print("原始纬度 = ");//Raw latitude
            // Serial.print(gps.location.rawLat().negative ? "-" : "+");
            // Serial.println(gps.location.rawLat().deg);
            // Serial.println(gps.location.rawLat().billionths);
            // Serial.print("原始经度 = ");//Raw longitude
            // Serial.print(gps.location.rawLng().negative ? "-" : "+");
            // Serial.println(gps.location.rawLng().deg);
            // Serial.println(gps.location.rawLng().billionths);
            // Serial.print("原始日期DDMMYY = ");//Raw date DDMMYY
            // Serial.println(gps.date.value());
            // Serial.print("年 = ");//Year
            // Serial.println(gps.date.year());
            // Serial.print("月 = ");//Month
            // Serial.println(gps.date.month());
            // Serial.print("日 = ");//Day
            // Serial.println(gps.date.day());
            // Serial.print("HHMMSCC中的原始时间 = ");//Raw time in HHMMSerial1CC
            // Serial.println(gps.time.value());
            // Serial.print("小时 = ");//Hour
            // Serial.println(gps.time.hour());
            // Serial.print("分钟 = ");//Minute
            // Serial.println(gps.time.minute());
            // Serial.print("秒 = ");//Second
            // Serial.println(gps.time.second());
            // Serial.print("百分之一秒 = ");//Centisecond
            // Serial.println(gps.time.centisecond());
            // Serial.print("原始速度（单位：100ths/knot） = ");//Raw speed in 100ths/knot
            // Serial.println(gps.speed.value());
            // Serial.print("速度（节/小时） = ");//Speed in knots/h
            // Serial.println(gps.speed.knots());
            // Serial.println(gps.speed.mph());
            // Serial.print("速度米/秒 = ");//Speed in m/s
            // Serial.println(gps.speed.mps());
            // Serial.print("速度每小时/公里 = ");//Speed in km/h
            // Serial.println(gps.speed.kmph());
            // Serial.print("原始课程（以度为单位） = ");//Raw course in degrees
            // Serial.println(gps.course.value());
            // Serial.print("Course in degrees = ");//Course in degrees
            // Serial.println(gps.course.deg());
            // Serial.print("原始高度（厘米） = ");//Raw altitude in centimeters
            // Serial.println(gps.altitude.value());
            // Serial.print("海拔高度（米） = ");//Altitude in meters
            // Serial.println(gps.altitude.meters());
            // Serial.print("海拔高度（英里） = ");//Altitude in miles
            // Serial.println(gps.altitude.miles());
            // Serial.print("海拔高度（千米） = ");//Altitude in kilometers
            // Serial.println(gps.altitude.kilometers());
            // Serial.print("海拔高度（英尺） = ");//Altitude in feet
            // Serial.println(gps.altitude.feet());
            // Serial.print("正在使用的卫星数量 = ");//Number os satellites in use
            // Serial.println(gps.satellites.value());
            // Serial.print("HDOP = ");
            // Serial.println(gps.hdop.value());
            // Serial.println("--------------------------------------");
            // Serial.println(gps.altitude.kilometers());
            // Serial.print("海拔高度（英尺） = ");//Altitude in feet
            // Serial.println(gps.altitude.feet());
            // Serial.print("正在使用的卫星数量 = ");//Number os satellites in use
            // Serial.println(gps.satellites.value());
            // Serial.print("HDOP = ");
            // Serial.println(gps.hdop.value());
            // Serial.println("--------------------------------------");
            Serial.println(Serial1.read());
        }
    } else {
        Serial.println("Not available.");
    }
    // delay(100);
    delay(1000);
}
