#include <WiFi.h>

const char* ssid = "SSID";
const char* password = "PASSWORT";

WiFiServer server(80);

String header;

boolean  server_en = true;

void webserverInit(){
  if (server_en){   //Webserver eingeschaltet
      WiFi.begin(ssid, password);
      Serial.print("Versuche WLAN-Verbindung");
      aufDisplayAnzeigen(0, 0, "Versuche Wlan verbindung");
     while (WiFi.status() != WL_CONNECTED) 
      {  delay(500);
         Serial.print(".");
      }
      Serial.println("");
      Serial.println("WiFi connected.");
      Serial.println("IP address: ");
      Serial.println(WiFi.localIP());
      aufDisplayAnzeigen(0, 20, "Erfolg");
      delay(1000);
      server.begin();
  }
}

boolean wifiStatus(){
  return WiFi.status() == WL_CONNECTED;
}


void webserverClientUeberpruefen() {
    WiFiClient client = server.available(); // Listen for incoming clients
    
    if (client){ 
        String header = client.readStringUntil('\r');
        client.println("HTTP/1.1 200 OK");
        client.println("Content-type:text/html");
        client.println("Connection: close");
        client.println();
        
        // Display the HTML web page
        client.println("<!DOCTYPE html><html>");
        client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
        client.println("<link rel=\"icon\" href=\"data:,\">");
        // CSS to style the on/off buttons 
        // Feel free to change the background-color and font-size attributes to fit your preferences
        client.println("<style>body { text-align: center; font-family: \"Trebuchet MS\", Arial; margin-left:auto; margin-right:auto;}");
        client.println(".slider { width: 300px; }</style>");
        client.println("<script src=\"https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js\"></script>");
        
        // Web Page
        client.println("</head><body><h1>ESP32 with Servo</h1>");
        client.println("<p>Position: <span id=\"servoPos\"></span></p>"); 
        client.println("<input type=\"range\" min=\"0\" max=\"180\" class=\"slider\" id=\"servoSlider\" onchange=\"servo(this.value)\" value=\"""\"/>");
        
        client.println("<script>var slider = document.getElementById(\"servoSlider\");");
        client.println("var servoP = document.getElementById(\"servoPos\"); servoP.innerHTML = slider.value;");
        client.println("slider.oninput = function() { slider.value = this.value; servoP.innerHTML = this.value; }");
        client.println("$.ajaxSetup({timeout:1000}); function servo(pos) { ");
        client.println("$.get(\"/?value=\" + pos + \"&\"); {Connection: close};}</script>");
        
        client.println("</body></html>"); 
        
        client.stop();
        Serial.println("Client disconnected.");
        Serial.println("");
    }
}
