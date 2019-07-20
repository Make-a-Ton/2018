#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "Myhotspote";

const char* password = "1234567898";

byte LED = 2;                // device to control
char BT_input = ' ';
String WF_input = " ";
//IPAddress staticIP(192,168,1,22);

//IPAddress gateway(192,168,1,9);

//IPAddress subnet(255,255,255,0);


void setup(void)

{
  Serial.begin(9600);     // default baud rate of module
  pinMode(LED, OUTPUT);
  //Serial.begin(115200);

  Serial.println();

  Serial.printf("Connecting to %s\n", ssid);

  WiFi.begin(ssid, password);

  //WiFi.config(staticIP, gateway, subnet);

  //  while (WiFi.status() != WL_CONNECTED)
  //
  //  {
  //
  //    delay(500);
  //
  //    Serial.print(".");
  //
  //  }

  Serial.println();
  digitalWrite(LED, HIGH);

}
int cnt=0;
void loop() {
  if (WiFi.status() == WL_CONNECTED && cnt>=100)

  {
    Serial.print("Connected, IP address: "); 
    Serial.println(WiFi.localIP());
    HTTPClient http;  //Declare an object of class HTTPClient

    http.begin("http://pabloscoba.000webhostapp.com/getdata.php");
    int httpCode = http.GET();                                                                 
    Serial.println(httpCode);
    if (httpCode > 0) { //Check the returning code

      String payload = http.getString();
      payload.trim();
      Serial.println(payload);
      WF_input = payload;
    }
    http.end();  //Close connection

  }
  if (Serial.available())
  {
    BT_input = Serial.read();

  }
  if ( BT_input == '0' || WF_input == "0")    //ascii code for 0 is dec 48
  {
    digitalWrite(LED, LOW);
    Serial.println(BT_input);
    WF_input = "0";
    BT_input = '0';
    Serial.println("RELAY is OFF");
  }
//  else if ( BT_input == '1' || WF_input == "1")
//  {
//    digitalWrite(LED, HIGH);
//    Serial.println(BT_input);
//    Serial.println("LED is ON");  //ascii code for 1 is dec 49
//  }
cnt++;
delay(10);
}
