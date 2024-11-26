#include <Arduino.h>              // Arduino Bibliothek                 
#include <Adafruit_ST7735.h>      // Adafruit ST7735 Bibliothek
#include <TinyGPSPlus.h>          // TinyGPS++ Bibliothek
#include <WiFi.h>                 // WiFi Bibliothek
#include <sMQTTBroker.h>          // sMQTTBroker Bibliothek
#include <ArduinoJson.h>             // ArduinoJson Bibliothek
#include <Wire.h>
#ifdef LED_BUILTIN
#undef LED_BUILTIN
#endif
#define LED_BUILTIN 18
#define VBAT_PIN 1
#define VBAT_READ_CNTRL_PIN 37 // Heltec GPIO to toggle VBatt read connection …
// Also, take care NOT to have ADC read connection
// in OPEN DRAIN when GPIO goes HIGH
#define ADC_READ_STABILIZE 10 // in ms (delay from GPIO control and ADC connections times)

// GNSS
#define VEXT_CTL 3
#define GPS_RX 33
#define GPS_TX 34
// Display
#define TFT_LED  21
#define TFT_CS   38
#define TFT_RST  39
#define TFT_DC   40
#define TFT_SCLK 41
#define TFT_MOSI 42

// Wifi
#define WIFI_SSID     "ESP32_AP_"
#define WIFI_PASSWORD "12345678"

// MQTT
#define MQTT_PORT      1883
sMQTTBroker Broker;
uint64_t chipid = ESP.getEfuseMac();
String chipID_str = String(chipid, HEX);
String short_chipID_str = chipID_str.substring(5);

TinyGPSPlus gps;
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

void setup_gps() {
    Serial1.begin(115200, SERIAL_8N1, GPS_RX, GPS_TX);

}
void setup_wifi() {
    Serial.print(F("[ESP32] Initialisiere WiFi ... "));
  //WiFi init
    WiFi.softAP((WIFI_SSID + chipID_str).c_str(), WIFI_PASSWORD);
   Serial.print(F("Erfolgreich!\n"));

}
void setup_mqtt() {
  //sMQTTbroker init
    Serial.print(F("[ESP32] Initialisiere sMQTT ... "));
    Broker.init(MQTT_PORT);
   Serial.print(F("Erfolgreich!\n"));
        //Json init
}
void setup_json() {
        //Json init
}

void setup_tft() {
    pinMode(TFT_CS, OUTPUT);
    pinMode(TFT_RST, OUTPUT);
    tft.initR(INITR_MINI160x80_PLUGIN);
    tft.setRotation(1);
    tft.fillScreen(ST77XX_BLACK);
    tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
    delay(50);
    pinMode(TFT_LED, OUTPUT);
    digitalWrite(TFT_LED, HIGH);
}

float readBatLevel() {
  int analogValue = analogRead(VBAT_PIN);
  float voltage = 0.0041 * analogValue;
  return voltage;
}



void setup() {
        Serial.begin(9200);
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);
    pinMode(VEXT_CTL, OUTPUT);
    digitalWrite(VEXT_CTL, HIGH);

    setup_tft();
    setup_gps();
    setup_wifi();
    setup_mqtt();
    setup_json();
  pinMode(VBAT_READ_CNTRL_PIN,OUTPUT);
  digitalWrite(VBAT_READ_CNTRL_PIN, LOW);

    tft.setCursor(0, 0);
    tft.print("GPS searching...");
    digitalWrite(LED_BUILTIN, LOW);
}

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
    tft.print("Satellites: ");
    tft.print(gps.satellites.value());
    tft.setCursor(0, 72);       
    tft.print("Bat: ");
    tft.print("4.21V       11:45 Uhr");



}
