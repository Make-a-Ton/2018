  #include <ESP8266WiFi.h>        // Include the Wi-Fi library
#include <String.h>
const char* ssid     = "mathew";         // The SSID (name) of the Wi-Fi network you want to connect to
const char* password = "lunargrey";     // The password of the Wi-Fi network

void setup() {
  Serial.begin(115200);         // Start the Serial communication to send messages to the computer
  delay(10);
  Serial.println('\n');


  //Static IP address configuration
  IPAddress staticIP(192, 168, 43, 10); //ESP static ip
  IPAddress gateway(192, 168, 43, 1);   //IP Address of your WiFi Router (Gateway)
  IPAddress subnet(255, 255, 255, 0);  //Subnet mask
  IPAddress dns(8, 8, 8, 8);  //DNS
  const char* deviceName = "esp1";

 WiFi.hostname(deviceName);      // DHCP Hostname (useful for finding device for static lease)
  WiFi.config(staticIP, subnet, gateway, dns);
  WiFi.begin(ssid, password);             // Connect to the network
  Serial.print("Connecting to ");
  Serial.print(ssid); Serial.println(" ...");

  int i = 0;
  while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
    delay(1000);
    Serial.print(++i); Serial.print(' ');
  }

  Serial.println('\n');
  Serial.println("Connection established!");
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());         // Send the IP address of the ESP8266 to the computer
}

void loop()
{
  const uint16_t port = 3000;
  const char * host = "192.168.43.118"; // ip or dns



  Serial.print("connecting to ");
  Serial.println(host);
WiFiClient client;
  // Use WiFiClient class to create TCP connections
  

  if (!client.connect(host, port)) {
    Serial.println("connection failed");
    Serial.println("wait 5 sec...");
    delay(5000);
    return;
  }

  // This will send the request to the server
  while(1)
  {
  client.print("deviceId=1&deviceName=A&deviceType=Humidity&inputValue=250");

  //read back one line from server
  //String line = client.readStringUntil('\r');
  //client.println(line);
  // field1=value1&field2=value2

  Serial.println("deviceId=1&deviceName=A&deviceType=Humidity&inputValue=250");


  Serial.println("wait 5 sec...");
  delay(5000);
}
}
