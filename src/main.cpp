#include <Arduino.h>              // Arduino Bibliothek                 
#include <Adafruit_ST7735.h>      // Adafruit ST7735 Bibliothek
#include <TinyGPSPlus.h>          // TinyGPS++ Bibliothek
#include <WiFi.h>                 // WiFi Bibliothek
#include <sMQTTBroker.h>          // sMQTTBroker Bibliothek
#include <ArduinoJson.h>          // ArduinoJson Bibliothek
#include <Wire.h>                 // Wire Bibliothek
#include <string>
#include "setup.h"
#include "display_updates.h"


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
    display_update_device();
    delay(5000);
    display_search_lora_devices();
    delay(5000);
    display_update_distances("9876", 1123.45, "5432", 543.21);
    delay(5000);
}
