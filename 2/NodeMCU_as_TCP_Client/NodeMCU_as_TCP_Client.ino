#include <ESP8266WiFi.h>
#define SERVER_PORT 8000

#include "DHT.h"
#define DHTPIN 0
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

IPAddress server_ip = {192,168,1,129};
const char* ssid = "teerawut_2.4G";
const char* password = "Hme1164741";
WiFiServer server(SERVER_PORT);
WiFiClient client;

void setup() {
  Serial.begin(115200);
  dht.begin();
  WiFi.begin(ssid, password); //เชื่อมต่อกับ AP
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  Serial.println("Connect TCP Server");
  while (!client.connect(server_ip,SERVER_PORT)) {
    Serial.print(".");
    delay(100);
  }
  Serial.println("Success");
}

void loop() {
  //DHT part
  // Wait a few seconds between measurements.
  delay(2000);
  // Reading temperature or humidity takes about 250 milliseconds!
  float h = dht.readHumidity(); // Celsius
  float t = dht.readTemperature(); //Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
  return;
  }
  
  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);
  
  Serial.print(F("Humidity: "));
  Serial.println(h);
  Serial.print(F("% Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.println("");
  //-----------------------------------------------------------------
  
  while(client.available()) {
    uint8_t data = client.read();
    Serial.write(data);
  }
  client.printf("Humidity: %.2f | Temperature: %.2f°C\n", h, t);
  delay(2000);
}
