const int trigPin = 5;
const int echoPin = 6;
// defines variables
long duration;
int distance1,distance2,distance3,distance,i;

int state = 0;
const int pin = 2;


void setup() {
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
Serial.begin(9600); // Starts the serial communication
}
void loop() {

  beginning:
// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculating the distance
distance1= duration*0.034/2;
// Prints the distance on the Serial Monitor
Serial.print("Distance1: ");
Serial.println(distance1);


delay(1000);

digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculating the distance
distance2= duration*0.034/2;
// Prints the distance on the Serial Monitor
Serial.print("Distance2: ");
Serial.println(distance2);


delay(1000);

digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculating the distance
distance3= duration*0.034/2;
// Prints the distance on the Serial Monitor
Serial.print("Distance3: ");
Serial.println(distance3);

delay(1000);

distance=(distance1+distance2+distance3)/3;


if(distance<10)
{i=0;
Serial.print("i ");
Serial.println(i);
}
else
{i=1;
  Serial.print("i ");
Serial.println(i);
}
delay(200);


if (i == 0 && state == 0) {
    Serial.print("\r");
    delay(1000);
    Serial.print("AT+CMGF=1\r");
    delay(1000);
    /*Replace XXXXXXXXXX to 10 digit mobile number & ZZ to 2 digit country code*/
    Serial.print("AT+CMGS=\"+918078180958\"\r");
    delay(1000);
    //The text of the message to be sent.
    Serial.print("Bin 1 is full");
    delay(1000);
    Serial.write(0x1A);
    delay(1000);
    state = 1;
   if(i)
    goto beginning;

  return 0;
  }
  else {
    state = 0;
    if(i)
    goto beginning;
  }

}
