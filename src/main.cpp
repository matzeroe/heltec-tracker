#include "setup.h"
#include <Arduino.h>              // Arduino Bibliothek                 
#include <Adafruit_ST7735.h>      // Adafruit ST7735 Bibliothek
#include <TinyGPSPlus.h>          // TinyGPS++ Bibliothek
#include <WiFi.h>                 // WiFi Bibliothek
#include <sMQTTBroker.h>          // sMQTTBroker Bibliothek
#include <ArduinoJson.h>          // ArduinoJson Bibliothek
#include <Wire.h>                 // Wire Bibliothek

void loop() {
    if (gps.time.isUpdated()) {
        tft.setCursor(0, 0);
        tft.printf("%04u-%02u-%02u %02u:%02u:%02u",
                   gps.date.year(), gps.date.month(), gps.date.day(),
                   gps.time.hour(), gps.time.minute(), gps.time.second());
    }

    if (gps.location.isUpdated()) {
        tft.setCursor(0, 12);
        tft.printf("Lat: % 3.6f\nLon: % 3.6f\n", gps.location.lat(), gps.location.lng());
    }
    if (gps.altitude.isUpdated()) {
        tft.setCursor(0, 28);
        tft.printf("Alt: %3.0fft ", gps.altitude.feet());
    }
    //digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    delay(1000);
    tft.setCursor(0, 0);
    tft.print("Device ID: ");
    tft.print(short_chipID_str);
    tft.setCursor(0, 12);
    tft.print("Distanz: ");
    tft.setCursor(0, 24);
    tft.print("--> ");
    tft.print("ID: 9876");
    tft.print("   730.2 M");
    tft.setCursor(0, 36);
    tft.print("--> ");
    tft.print("ID: 4321");
    tft.print("   3821.2 M");
    tft.setCursor(0, 48);
    tft.print("--> ");
    tft.print("ID: 1234");
    tft.print("   50.1 M");
    tft.setCursor(0, 60);
    tft.print("Satelitten: ");
    tft.print(gps.satellites.value());
    tft.setCursor(0, 72);       
    tft.print("Bat: ");
    tft.print("4.21V       11:45 Uhr");
}
