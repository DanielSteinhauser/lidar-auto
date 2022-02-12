# lidar-auto
Technisches Projekt

Website ESP32:  https://heltec.org/project/wifi-kit-32/ 

H-Brücke:  https://funduino.de/nr-34-motoren-mit-h-bruecke-l298n-ansteuern

## IDE Setup

### Boardverwalter:
Datei -> Voreinstellungen -> Zusätzliche Boardverwalter-URLs: 
`https://github.com/Heltec-Aaron-Lee/WiFi_Kit_series/releases/download/0.0.5/package_heltec_esp32_index.json
`
Werkzeuge -> Board -> Boardverwalter -> Suchfeld: Heltec esp32 Devboards  -> Neueste Version Installieren

### Librarys:
Werkzeuge -> Bibliotheken verwalten: 
`Heltec esp32 Dev-boards`,
`EspMQTTClient` 
(Dependencys immer mit installieren)

### Richtiges Board auswählen:
Werkzeuge -> Board -> Heltec ESP32 Arduino -> Wifi Kit 32
