#include<SoftwareSerial.h>
SoftwareSerial BTserial(10,11);//rx n tx
int x=HIGH;  
int y=HIGH;
void setup() 
{
pinMode(5,OUTPUT); 
pinMode(6,INPUT);
pinMode(7,INPUT);
pinMode(8,OUTPUT);

Serial.begin(9600);
BTserial.begin(9600);
 
  // put your setup code here, to run once:

}


void loop() 
{
  y=digitalRead(7);
  x=digitalRead(6);
  if(x==0)
  {
    Serial.println("BRO an obstacle ahead sensor");
    
    digitalWrite(5,HIGH);
    // put your main code here, to run repeatedly:
    BTserial.println("obstacle on the right side");
  }
else
{ 
Serial.println("situation is clear,that was so easy");
digitalWrite(5,LOW);
}
if(y==0)
{
  digitalWrite(8,HIGH);
 
BTserial.println("obstacle on the left side"); 

 
}

else
{
  digitalWrite(8,LOW);
}
if(x==0 && y==0)
{
  digitalWrite(5,HIGH);
  digitalWrite(8,HIGH);
  BTserial.println("something ahead of you"); 
}
delay(500);
}
  
