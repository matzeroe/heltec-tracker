// Funktion zur Berechnung des Abstands zwischen zwei GPS-Koordinaten
// Verwendet die Haversine-Formel
// Eingabe: Breite (lat) und Länge (lon) in Grad für beide Positionen
// Ausgabe: Abstand in Metern
double berechneAbstandInMeter(double lat1, double lon1, double lat2, double lon2) {
    // Erdradius in Metern
    const double erdRadius = 6371000.0;
    
    // Umrechnung von Grad in Radian
    lat1 = lat1 * M_PI / 180.0;
    lon1 = lon1 * M_PI / 180.0;
    lat2 = lat2 * M_PI / 180.0;
    lon2 = lon2 * M_PI / 180.0;
    
    // Differenzen der Koordinaten
    double dLat = lat2 - lat1;
    double dLon = lon2 - lon1;
    
    // Haversine Formel
    double a = sin(dLat/2) * sin(dLat/2) +
               cos(lat1) * cos(lat2) * 
               sin(dLon/2) * sin(dLon/2);
    
    double c = 2 * atan2(sqrt(a), sqrt(1-a));
    
    // Berechnung der Distanz in Metern
    double distanz = erdRadius * c;
    
    return distanz;
}

// Beispiel zur Verwendung:
// double abstand = berechneAbstandInMeter(48.137154, 11.576124, 48.137254, 11.576224);