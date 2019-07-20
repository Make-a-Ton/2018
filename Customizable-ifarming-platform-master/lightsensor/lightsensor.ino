#include <ESP8266WiFi.h>       
#include<String.h>
const char* ssid     = "mathew";        
const char* password = "lunargrey";     


int lightval = 0;
void setup() {
  pinMode(A0, LOW);
  Serial.begin(115200);        
  delay(10);
  Serial.println('\n');


  
  IPAddress staticIP(192, 168, 43, 10); 
  IPAddress gateway(192, 168, 43, 1);   
  IPAddress subnet(255, 255, 255, 0);  
  IPAddress dns(8, 8, 8, 8);  
  const char* deviceName = "lightsensor";

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



  Serial.print("connecting to ");
  Serial.println(host);
  WiFiClient client;
  

  if (!client.connect(host, port)) {
    Serial.println("connection failed");
    Serial.println("wait 5 sec...");
    delay(5000);
    return;
  }

 

  lightval = analogRead(A0);
  client.print("deviceId=1&deviceName=lightsensor_only&deviceType=Lightsensor&inputValue=" + String(lightval));


 

  Serial.println("deviceId=1&deviceName=lightsensor_only&deviceType=Lightsensor&inputValue=" + String(lightval));


  Serial.println("wait 5 sec...");
  delay(5000);
  client.stop();
}
s
