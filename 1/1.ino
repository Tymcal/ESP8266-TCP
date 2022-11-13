#include <ESP8266WiFi.h>

int ledPin = 4;

#define SERVER_PORT 8000
const char* ssid = "teerawut_2.4G";
const char* password = "Hme1164741";
WiFiServer server(SERVER_PORT);

void setup() {
  Serial.begin(115200);
  delay(10);

  //------------------------------------------------
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, 0);
  //------------------------------------------------
  
  // Connect to WiFi network
  Serial.println();
  Serial.println("");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
  Serial.println("Server started");
}

void loop() {
  
  WiFiClient client = server.available();
  if (client) {
    Serial.println("new client");
    while(1) {
      while(client.available()) {
        String data =client.readStringUntil('\n');
        Serial.println((String)data);
        if (data == "1") {
          digitalWrite(ledPin, 1);
        } else if (data == "0") {
          digitalWrite(ledPin, 0);
        } else {
          Serial.println("Bruh");
        }
      }
      if(server.hasClient()) {
        return; //ถ้าไมม่ีใ􏰃้ออกจากลูปไปเรมิ่ตน้รอรับClientใ􏰃ม่
      }
    }
  }
  client.flush();
}
