#include <Arduino.h>
#include <Adafruit_ST7735.h>
#include <TinyGPSPlus.h>

#ifdef LED_BUILTIN
#undef LED_BUILTIN
#endif
#define LED_BUILTIN 18

#define VEXT_CTL 3

#define GPS_RX 33
#define GPS_TX 34

#define TFT_LED  21
#define TFT_CS   38
#define TFT_RST  39
#define TFT_DC   40
#define TFT_SCLK 41
#define TFT_MOSI 42

TinyGPSPlus gps;
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

void setup_gps()
{    
    Serial1.begin(115200, SERIAL_8N1, GPS_RX, GPS_TX);
}

void setup_tft()
{
    pinMode(TFT_CS, OUTPUT);
    pinMode(TFT_RST, OUTPUT);
    pinMode(TFT_CS, OUTPUT);

    tft.initR(INITR_MINI160x80_PLUGIN);
    tft.setRotation(1); // Landscape
    tft.fillScreen(ST77XX_BLACK);
    tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);

    delay(50); // Wait for screen to clear

    // Enable backlight
    pinMode(TFT_LED, OUTPUT);
    digitalWrite(TFT_LED, HIGH);
}


void setup() 
{
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);

    // Enable power to peripherals
    pinMode(VEXT_CTL, OUTPUT);
    digitalWrite(VEXT_CTL, HIGH);
    
    setup_tft();
    setup_gps();

    tft.setCursor(0, 0);
    tft.print("GPS searching...");

    digitalWrite(LED_BUILTIN, LOW);
}

void run_tasks(uint32_t ms)
{
    unsigned long start = millis();

    do
    {
        while (Serial1.available())
            gps.encode(Serial1.read());
    } while (millis() - start < ms);
}

void loop() 
{
    if (gps.time.isUpdated())
    {
        tft.setCursor(0, 0);
        tft.printf("%04u-%02u-%02u %02u:%02u:%02u",
                   gps.date.year(), gps.date.month(), gps.date.day(),
                   gps.time.hour(), gps.time.minute(), gps.time.second());
    }

    if (gps.location.isUpdated())
    {
        tft.setCursor(0, 12);
        tft.printf("Lat: % 3.6f\nLon: % 3.6f\n", gps.location.lat(), gps.location.lng());
    }

    if (gps.altitude.isUpdated())
    {
        tft.setCursor(0, 28);
        tft.printf("Alt: %3.0fft ", gps.altitude.feet());
    }

    run_tasks(1000);
}
