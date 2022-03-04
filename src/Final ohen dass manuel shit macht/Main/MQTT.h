//Verarbeitung empfangene Daten
void callback(char* topic, byte* message, unsigned int length) {
    Serial.print("Message arrived on topic: ");
    Serial.print(topic);
    Serial.print(". Message: ");
    String messageTemp = "";
    
    for (int i = 0; i < length; i++) {
        Serial.print((char)message[i]);
        messageTemp += (char)message[i];
    }
    Serial.println();
    
    if (String(topic) == "gswt/herbert") 
    {
        if (messageTemp == "0"){
            Serial.println("Ändere Modus zu Ruhe.");
            zustand = 0;
        } else if (messageTemp == "1"){
            Serial.println("Ändere Modus zu autonomem fahren.");
            zustand = 1;
        } else if (messageTemp == "2") {
            Serial.println("Ändere Modus zu manuell.");
            zustand = 2;
        } else {
            Serial.println("Error: ändere vorsichtshalber Modus zu Ruhe");
            zustand = 0;
        }
    }
}

void mqttInit(){
      WiFi.begin(ssid, password);
      
      Serial.print("Versuche WLAN-Verbindung");
      aufDisplayAnzeigen(0, 0, "Versuche Wlan verbindung");
      
      for(int i = 0; i < 10; ++i){
        if (WiFi.status() == WL_CONNECTED){         //sobald WLan verbunden
            Serial.println("");
            Serial.println("WiFi connected.");
            Serial.println("IP address: ");
            Serial.println(WiFi.localIP());
            aufDisplayAnzeigen(0, 10, "verbunden.");
            aufDisplayAnzeigen(0, 20, String(WiFi.localIP()) );
            client.setServer(server, 1883);
            client.setCallback(callback);
            
            if (client.connect("Herbert")) {
                Serial.println("Connected to MQTT-Broker.");
                aufDisplayAnzeigen(0, 30, "MQTT Server verbunden.");
                client.subscribe(topicSubscribe);
                aufDisplayAnzeigen(0, 40, "herbert topic subscribed.");
                client.publish(topicPublish, "Herbert ist online");
            }
            wlan_verbunden = true;
            break;
        } 
        else {
          Serial.print(".");  //
          delay(500);
        }
      }
      
      if (WiFi.status() != WL_CONNECTED){
        Serial.println("WLAN-Verbindung fehlgeschlagen.");
        aufDisplayAnzeigen(0, 10, "WLAN FEHLER.");
        aufDisplayAnzeigen(0, 20, "wechsle Startzustand zu 1.");
        zustand = 1;
      }
      
      delay(3000);
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("Herbert")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish(topicPublish, "Herbert ist online");
      // ... and resubscribe
      client.subscribe(topicSubscribe);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}




void mqttAbrufen(){
  if(wlan_verbunden){
      if (!client.connected()) { // sichern dass MQTT verbunden ist
       Serial.println("MQTT Verbindung verloren");
       reconnect();
      }
      client.loop(); // neue Daten abholen, führt bei neuer Nachricht callback() aus
  }
}
 
