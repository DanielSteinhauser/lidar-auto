# lidar-auto
Technisches Projekt

Website ESP32:  https://heltec.org/project/wifi-kit-32/ 
H-Brücke:  https://funduino.de/nr-34-motoren-mit-h-bruecke-l298n-ansteuern

## IDE Setup

### Boardverwalter:
Datei -> Voreinstellungen -> Zusätzliche Boardverwalter-URLs: 
`https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
https://github.com/Heltec-Aaron-Lee/WiFi_Kit_series/releases/download/0.0.5/package_heltec_esp32_index.json
`
Werkzeuge -> Board -> Boardverwalter -> Suchfeld: Heltec esp32 Devboards  -> Neueste Version Installieren

### Librarys:
**Heltec esp32 Library:**
Werkzeuge -> Bibliotheken verwalten... -> Suchfeld: `Heltec esp32 Devboards` , neueste Version 

**ESPAsyncWebServer,  AsyncTCP Library:**
Sketch -> Bibliothek einbinden -> .Zip Bibliothek -> beide auswählen

### Richtiges Board auswählen:
Werkzeuge -> Board -> Heltec ESP32 Arduino -> Wifi Kit 32
