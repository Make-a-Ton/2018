#include <ESP8266WiFi.h>       
#include<String.h>
#include "DHTesp.h"      
DHTesp dht;

const char* ssid     = "mathew";       
const char* password = "lunargrey";    



void setup() {
  dht.setup(4, DHTesp::DHT11);
  Serial.begin(115200);        
  delay(10);



  IPAddress staticIP(192, 168, 43, 30); 
  IPAddress gateway(192, 168, 43, 1); 
  IPAddress subnet(255, 255, 255, 0);  
  IPAddress dns(8, 8, 8, 8); 
  const char* deviceName = "temphumiditysensor";

  WiFi.hostname(deviceName);      
  WiFi.config(staticIP, subnet, gateway, dns);
  WiFi.begin(ssid, password);           
  Serial.print("Connecting to ");
  Serial.print(ssid); Serial.println(" ...");

  int i = 0;
  while (WiFi.status() != WL_CONNECTED) { 
    delay(1000);
    Serial.print(++i); Serial.print(' ');
  }

  Serial.println('\n');
  Serial.println("Connection established!");
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());       
}

void loop()
{
  const uint16_t port = 3000;
  const char * host = "192.168.43.118";
  Serial.println(host);
  delay(dht.getMinimumSamplingPeriod());

  float h = dht.getHumidity();
  float t = dht.getTemperature();
  Serial.print("connecting to ");
  Serial.println("temperature" + String(t) + ";humidity" + String(h));

  WiFiClient client;

  if (!client.connect(host, port)) {
    Serial.println("connection failed");
    Serial.println("wait 5 sec...");
    delay(5000);
    return;
  }

   client.print("deviceId=3&deviceName=tempsensor_only&deviceType=tempsensor&inputValue=" + String(t));
  delay(500);
   client.print("deviceId=4&deviceName=humiditysensor_only&deviceType=humiditysensor&inputValue=" + String(h));

   Serial.println("deviceId=3&deviceName=tempsensor_only&deviceType=tempsensor&inputValue=" + String(t));
  Serial.println("deviceId=4&deviceName=humiditysensor_only&deviceType=humiditysensor&inputValue=" + String(h));


  Serial.println("wait 5 sec...");
  delay(5000);
  client.stop();
}

