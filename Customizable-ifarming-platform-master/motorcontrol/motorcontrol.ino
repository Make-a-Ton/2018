#include <ESP8266WiFi.h>       


const char* ssid     = "mathew";        
const char* password = "lunargrey";    
String c;

void setup() {
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  Serial.begin(115200);        
  delay(10);
  Serial.println('\n');


  IPAddress staticIP(192, 168, 43, 5); 
  IPAddress gateway(192, 168, 43, 1);   
  IPAddress subnet(255, 255, 255, 0); 
  IPAddress dns(8, 8, 8, 8); 
  const char* deviceName = "motorctrl";

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
void loop() {
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
  client.print("hello");
  
  while (1)
  {

    
    int i = 0;
    if (client.available()) {
      {
        c = client.readString();
        Serial.println(c);
      }
      delay(150);
       if (c.indexOf("motoron") >= 0)
       {
        digitalWrite(2,HIGH);
        delay(1000);
        digitalWrite(2,LOW);
        
       }
    }
  }
}

