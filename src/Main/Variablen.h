bool mqtt_en = true; // MQTT Hauptschalter
bool wlan_verbunden = false; // WLAN Zustand (nicht manuell ändern)
int zustand = 0; //Startzustand
int serialBefehl;

//Lidar
int16_t tfDist;
int16_t tfAddr = TFL_DEF_ADR;
bool distanzZuKurz = false;

// MQTT
const char* ssid = "BMW1000";
const char* password = "WoUtBa14";

const char* server = "test.mosquitto.org";

const char* topicPublish = "gswt/herbert/";   
const char* topicSubscribe = "gswt/#";

//Steuerung
int geschwindigkeit = 130;
int aus = 0;

//Scan
int rechtskurveDistanz = 0;
int linkskurveDistanz = 0;

int rechtskurveGrad = 0;
int linkskurveGrad = 0;
