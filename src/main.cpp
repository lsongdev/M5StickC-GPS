#include <M5StickC.h>
#include <TinyGPS++.h>

TinyGPSPlus gps;
HardwareSerial GPSRaw(2);

void setup() {
  M5.begin();
  M5.Lcd.setRotation(3);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextSize(1);
  
  GPSRaw.begin(9600, SERIAL_8N1, 33, 32);  // RX=G32, TX=G33
  
  M5.Lcd.setTextSize(2);
  M5.Lcd.println("GPS Example");
  M5.Lcd.setTextSize(1);
  M5.Lcd.println("Waiting for GPS signal...");
}

void displayGPSInfo() {
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.setTextSize(2);
  M5.Lcd.println("GPS Example");
  M5.Lcd.setTextSize(1);

  // 显示位置信息
  if (gps.location.isValid()) {
    M5.Lcd.print("Lat: ");
    M5.Lcd.println(gps.location.lat(), 6);
    M5.Lcd.print("Lng: ");
    M5.Lcd.println(gps.location.lng(), 6);
  } else {
    M5.Lcd.println("Location: Invalid");
  }
  
  // 显示时间信息
  if (gps.time.isValid()) {
    M5.Lcd.print("Time: ");
    if (gps.time.hour() < 10) M5.Lcd.print("0");
    M5.Lcd.print(gps.time.hour());
    M5.Lcd.print(":");
    if (gps.time.minute() < 10) M5.Lcd.print("0");
    M5.Lcd.print(gps.time.minute());
    M5.Lcd.print(":");
    if (gps.time.second() < 10) M5.Lcd.print("0");
    M5.Lcd.println(gps.time.second());
  } else {
    M5.Lcd.println("Time: Invalid");
  }
  
  // 显示卫星信息
  M5.Lcd.print("Satellites: ");
  if (gps.satellites.isValid()) {
    M5.Lcd.println(gps.satellites.value());
  } else {
    M5.Lcd.println("Invalid");
  }
  
  // 显示海拔信息
  M5.Lcd.print("Altitude: ");
  if (gps.altitude.isValid()) {
    M5.Lcd.print(gps.altitude.meters());
    M5.Lcd.println("m");
  } else {
    M5.Lcd.println("Invalid");
  }
  
  // 显示速度信息
  M5.Lcd.print("Speed: ");
  if (gps.speed.isValid()) {
    M5.Lcd.print(gps.speed.kmph());
    M5.Lcd.println("km/h");
  } else {
    M5.Lcd.println("Invalid");
  }
}

void loop() {
  while (GPSRaw.available() > 0) {
    if (gps.encode(GPSRaw.read())) {
      displayGPSInfo();
    }
  }

  // 检查 GPS 是否正常工作
  if (millis() > 5000 && gps.charsProcessed() < 10) {
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.println("No GPS detected");
    delay(1000);
  }
}
