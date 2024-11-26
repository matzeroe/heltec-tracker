„Entwicklung eines Systems zur Positions- und Distanzbestimmung in Echtzeit mittels GNSS- und LoRa(WAN)-Technologie“

Beschreibung:

Dieses Projekt befasst sich mit der präzisen Lokalisierung und Distanzbestimmung mehrerer akkubetriebener 32-Bit Microcontroller, die mit GNSS- und LoRa(WAN)-Modulen ausgestattet sind. Diese Kombination ermöglicht eine genaue Positionsbestimmung und drahtlose Kommunikation über große Entfernungen bei geringem Energieverbrauch und macht es so zu einem robusten System zur Echtzeit- Distanzbestimmung.

Ziel:

Das Ziel dieser Technikerarbeit ist es, ein System zu entwickeln, das die Positionen mehrerer Microcontroller präzise bestimmen und die Abstände zwischen ihnen messen kann. Die Positionen der einzelnen Nodes werden drahtlos mittels LoRa(WAN) zu den anderen Nodes übertragen und jeweils verrechnet. Anschließend wird der Abstand zwischen allen Trackern auf einem OLED-Display visualisiert. Die Positionen der Nodes sollen kontinuierlich drahtlos übertragen und verrechnet werden, sodass die Distanzen in Echtzeit auf einem OLED-Display angezeigt werden. Die genauen Standorte der einzelnen Nodes können bei Bedarf auch auf dem Smartphone verfolgt werden.

Technische Umsetzung:

Die Softwareentwicklung umfasst das Auslesen der Positionsdaten aus dem GNSS-Modul, das Versenden und Empfangen dieser mit dem LoRa(WAN)-Modul, die Berechnung der Distanzen in Luftlinie und die Aufbereitung dieser zur Darstellung auf dem Display. Außerdem werden die Daten mit einem MQTT-Broker auf dem Microcontroller über Wi-Fi zu einer quelloffenen Smartphone-App übermittelt. Zusätzlich wird ein Gehäuse entworfen, welches den Anforderungen hinsichtlich Robustheit gerecht werden und dabei handlich ist. Dieses Gehäuse soll mit 3D-Drucktechnologie gefertigt werden.
