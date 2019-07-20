 #include <LiquidCrystal.h>
#include <Servo.h>
Servo myservo; 
const int trigPin1 = 9;
const int echoPin1 = 10;
const int trigPin2 = 5;
const int echoPin2 = 6;
const int rs = 12, en = 11, d4 = 7, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
long duration1;
int distance1;
long duration2;
int distance2;
int l1=5,l2=0,f=0,pos,i;
float e;
long int o;
void setup() {
pinMode(trigPin2, OUTPUT); 
pinMode(echoPin2, INPUT); 
 lcd.begin(16, 2);
   myservo.attach(8);   
  
pinMode(trigPin1, OUTPUT); 
pinMode(echoPin1, INPUT); 

}
void loop() {
  
 
  

digitalWrite(trigPin2, LOW);
delayMicroseconds(2);
digitalWrite(trigPin2, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin2, LOW);
duration2 = pulseIn(echoPin2, HIGH);

distance2= duration2*(0.034/2);

digitalWrite(trigPin1, LOW);
delayMicroseconds(2);

digitalWrite(trigPin1, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin1, LOW);

duration1 = pulseIn(echoPin1, HIGH);
distance1= duration1*(0.034/2);



if(distance1<=30)
   {f=1;}

if(f==1)
 {
 
    myservo.write(0); 
  
  
  while(l1>=0)
   {
i=59;
     
while(i>=0)
{
 
lcd.setCursor(0,0);
lcd.print(l1);
lcd.print(":"); 
lcd.print(i);
i--;    
delay(100);
}

l1--;
    }
 }

if(distance2<=30)
 { 
  
    myservo.write(90);

 


l1=5;l2=0;f=0;
 } 
lcd.clear();
 
 
}

 
