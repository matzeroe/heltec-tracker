#include <string>

void display_update_device() {
    tft.setCursor(0, 0);
    tft.printf ("Device ID: %s", short_chipID_str);
    tft.setCursor(0, 48);
    tft.printf("Lon: %4.3f Lat: %4.3f    ", gps.location.lng(), gps.location.lat());
    tft.setCursor(0, 60);
    tft.printf ("SATs: %i", gps.satellites.value());
    tft.setCursor(0, 72);   
    tft.printf ("Bat: 4.21V  Time: 11:30 ", gps.time.hour(), gps.time.minute());
    }
void display_search_lora_devices() {
    tft.setCursor(0, 12);
    tft.printf ("LoRa Nodes suchen...             ");
    tft.setCursor(0, 24);
    tft.printf ("                           ");    
    tft.setCursor(0, 36);
    tft.printf("                         ");
}
void display_update_distances(String id_01, float distance_01, String id_02, float distance_02) {
    tft.setCursor(0, 12);
    tft.printf ("Distanz:          in Meter");
    tft.setCursor(0, 24);
    tft.printf("--> ID: %s        %4.1f", id_01, distance_01);
    tft.setCursor(0, 36);
    tft.printf("--> ID: %s        %4.1f", id_02, distance_02);
    }