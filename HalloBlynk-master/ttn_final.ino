/*******************************************************************************
 * Copyright (c) 2015 Thomas Telkamp and Matthijs Kooijman
 *
 * Permission is hereby granted, free of charge, to anyone
 * obtaining a copy of this document and accompanying files,
 * to do whatever they want with them without any restriction,
 * including, but not limited to, copying, modification and redistribution.
 * NO WARRANTY OF ANY KIND IS PROVIDED.
 *
 * This example sends a valid LoRaWAN packet with payload "Hello,
 * world!", using frequency and encryption settings matching those of
 * the (early prototype version of) The Things Network.
 *
 * Note: LoRaWAN per sub-band duty-cycle limitation is enforced (1% in g1,
 *  0.1% in g2).
 *
 * Change DEVADDR to a unique address!
 * See http://thethingsnetwork.org/wiki/AddressSpace
 *
 * Do not forget to define the radio type correctly in config.h.
 *
 *******************************************************************************/
#include "SSD1306.h" 
#include <lmic.h>
#include <hal/hal.h>
#include <SPI.h>
#include "DHT.h"
//#include "MQ135.h"

#include <NewPing.h>
#define MAX_DISTANCE 200



int tempPin = 34;

//NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);


#define ANALOGPIN 2

#define DHTPIN 13
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);






// Pulse Monitor Test Script
int sensorPin = 38;

unsigned int counter = 0;

//long duration;
//int distance;

SSD1306 display(0x3c, 4, 15);
String rssi = "RSSI --";
String packSize = "--";
String packet ;
// LoRaWAN NwkSKey, network session key
// This is the default Semtech key, which is used by the prototype TTN
// network initially.
//static const PROGMEM u1_t NWKSKEY[16] = { 0xBB, 0x3B, 0xCC, 0xB4, 0x88, 0x8B, 0x6B, 0x56, 0xDC, 0xA3, 0x58, 0xFB, 0x41, 0xCE, 0x56, 0x54 }; 
static const PROGMEM u1_t NWKSKEY[16] = { 0x10, 0x21, 0x5A, 0x6E, 0x76, 0x24, 0x8D, 0xDF, 0xCB, 0x89, 0xD0, 0x5B, 0xE4, 0x7D, 0x29, 0x98 }; 

// LoRaWAN AppSKey, application session key
// This is the default Semtech key, which is used by the prototype TTN
// network initially.
//static const u1_t PROGMEM APPSKEY[16] = { 0x7D, 0xE3, 0x63, 0x56, 0x82, 0x91, 0x68, 0xB0, 0xB6, 0x41, 0x7E, 0xC6, 0x78, 0x07, 0xF1, 0xEC };
static const u1_t PROGMEM APPSKEY[16] = { 0xC9, 0x9E, 0xF4, 0xE2, 0x1D, 0x8F, 0xDF, 0x29, 0xDA, 0xFE, 0x09, 0x6D, 0xA2, 0xD0, 0xF6, 0x37 };

// LoRaWAN end-device address (DevAddr)
// See http://thethingsnetwork.org/wiki/AddressSpace
//static const u4_t DEVADDR = 0x260116C3 ;
static const u4_t DEVADDR = 0x26011AF3 ;// <-- Change this address for every node!

// These callbacks are only used in over-the-air activation, so they are
// left empty here (we cannot leave them out completely unless
// DISABLE_JOIN is set in config.h, otherwise the linker will complain).
void os_getArtEui (u1_t* buf) { }
void os_getDevEui (u1_t* buf) { }
void os_getDevKey (u1_t* buf) { }

struct data {
int a;
int b;
int c;
int d;
}mydata;
static osjob_t sendjob;

// Schedule TX every this many seconds (might become longer due to duty
// cycle limitations).
const unsigned TX_INTERVAL = 3;

// Pin mapping
const lmic_pinmap lmic_pins = {
    .nss = 18,
    .rxtx = LMIC_UNUSED_PIN,
    .rst = 12,
    .dio = {26, 33, LMIC_UNUSED_PIN},
};

void onEvent (ev_t ev) {
    Serial.print(os_getTime());
    Serial.print(": ");
    switch(ev) {
        case EV_SCAN_TIMEOUT:
            Serial.println(F("EV_SCAN_TIMEOUT"));
            break;
        case EV_BEACON_FOUND:
            Serial.println(F("EV_BEACON_FOUND"));
            break;
        case EV_BEACON_MISSED:
            Serial.println(F("EV_BEACON_MISSED"));
            break;
        case EV_BEACON_TRACKED:
            Serial.println(F("EV_BEACON_TRACKED"));
            break;
        case EV_JOINING:
            Serial.println(F("EV_JOINING"));
            break;
        case EV_JOINED:
            Serial.println(F("EV_JOINED"));
            break;
        case EV_RFU1:
            Serial.println(F("EV_RFU1"));
            break;
        case EV_JOIN_FAILED:
            Serial.println(F("EV_JOIN_FAILED"));
            break;
        case EV_REJOIN_FAILED:
            Serial.println(F("EV_REJOIN_FAILED"));
            break;
            break;
        case EV_TXCOMPLETE:
            Serial.println(F("EV_TXCOMPLETE (includes waiting for RX windows)"));
            if(LMIC.dataLen) {
                // data received in rx slot after tx
                Serial.print(F("Data Received: "));
                Serial.write(LMIC.frame+LMIC.dataBeg, LMIC.dataLen);
                Serial.println();
            }
            // Schedule next transmission
            os_setTimedCallback(&sendjob, os_getTime()+sec2osticks(TX_INTERVAL), do_send);
            break;
        case EV_LOST_TSYNC:
            Serial.println(F("EV_LOST_TSYNC"));
            break;
        case EV_RESET:
            Serial.println(F("EV_RESET"));
            break;
        case EV_RXCOMPLETE:
            // data received in ping slot
            Serial.println(F("EV_RXCOMPLETE"));
            break;
        case EV_LINK_DEAD:
            Serial.println(F("EV_LINK_DEAD"));
            break;
        case EV_LINK_ALIVE:
            Serial.println(F("EV_LINK_ALIVE"));
            break;
         default:
            Serial.println(F("Unknown event"));
            break;
    }
}

void do_send(osjob_t* j){
  int h = dht.readHumidity();
// Read temperature as Celsius (the default)
int t = dht.readTemperature();
int x = analogRead(ANALOGPIN);



//int y = analogRead(12);
pinMode(33,INPUT);
pinMode(34,INPUT);
int z = digitalRead(21);
int z1 = digitalRead(12);
//float y = analogRead(34);



//Serial.println(x);
Serial.print("Humidity: ");
Serial.print(h);
Serial.print(" %\t");
Serial.print("Temperature: ");
Serial.print(t);
Serial.println("/n");
//Serial.println(z);
//Serial.println(y*1240.9);


/*unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
  Serial.print("Ping: ");
  Serial.print(sonar.convert_cm(uS)); // Convert ping time to distance and print result (0 = outside set distance range, no ping echo)
  Serial.println("cm");*/

int  reading = analogRead(tempPin);

int tempC = reading / 9.31;
Serial.println(tempC+15);


  


mydata.a=h;//(gps.location.lat()-8);
mydata.b=t;
mydata.c=x;
mydata.d=(tempC+10);

  
    // Check if there is not a current TX/RX job running
    if (LMIC.opmode & OP_TXRXPEND) {
        Serial.println(F("OP_TXRXPEND, not sending"));
    } else {
        // Prepare upstream data transmission at the next possible time.
        LMIC_setTxData2(1, (unsigned char *)&mydata, sizeof(mydata)-1, 0);
        Serial.println(F("Packet queued"));
        display.clear();
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_10);
  
  display.drawString(0, 0, "Humidity=" );
  display.drawString(90, 0, String(h));
  display.drawString(0, 10, "Temperature=" );
  display.drawString(90, 10, String(t));
  if(x>800)
  {
  display.drawString(0, 20, "Harmful Gas!!");
  }
  else if(x<1300)
  {
    display.drawString(0, 20, "            "); 
  }
  display.drawString(0, 30, "Distance=");
  display.drawString(90, 30, String(random(10,100)));
  display.drawString(0, 40, "Body-Temp=");
  display.drawString(90, 40, String(tempC+10));
  if(z==1)
  {
  display.drawString(0, 50, String(100));
    display.drawString(75, 50, "Spanners");
  }
  else if(z==0)
  {
    display.drawString(0, 50, "    ");
    display.drawString(75, 50, "         ");
  }

  if(z1==1)
  {
  display.drawString(0, 50, String(5));
    display.drawString(75, 50, "Lr Petrol");
  }
  else if(z1==0)
  {
    display.drawString(0, 50, "    ");
    display.drawString(75, 50, "         ");
  }
  
  
//  display.drawString(0, 30, String(cm));
  
  
  //delay(5000);
  
  display.display();
  counter++;
    }
     
    // Next TX is scheduled after TX_COMPLETE event.
}

void setup() {
    Serial.begin(115200);
    dht.begin();
    Serial.println(F("Starting"));
//    analogReference(INTERNAL);
    
pinMode(16,OUTPUT);
  pinMode(25,OUTPUT);
  pinMode(2,INPUT);
  pinMode(12,INPUT);
  pinMode(21,INPUT);
  pinMode(34,INPUT);
//  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
//pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  
  digitalWrite(16, LOW);    // set GPIO16 low to reset OLED
  delay(50); 
  digitalWrite(16, HIGH);
    #ifdef VCC_ENABLE
    // For Pinoccio Scout boards
    pinMode(VCC_ENABLE, OUTPUT);
    digitalWrite(VCC_ENABLE, HIGH);
    delay(1000);
    #endif

    // LMIC init
    os_init();
    // Reset the MAC state. Session and pending data transfers will be discarded.
    LMIC_reset();

    // Set static session parameters. Instead of dynamically establishing a session
    // by joining the network, precomputed session parameters are be provided.
    #ifdef PROGMEM
    // On AVR, these values are stored in flash and only copied to RAM
    // once. Copy them to a temporary buffer here, LMIC_setSession will
    // copy them into a buffer of its own again.
    uint8_t appskey[sizeof(APPSKEY)];
    uint8_t nwkskey[sizeof(NWKSKEY)];
    memcpy_P(appskey, APPSKEY, sizeof(APPSKEY));
    memcpy_P(nwkskey, NWKSKEY, sizeof(NWKSKEY));
    LMIC_setSession (0x1, DEVADDR, nwkskey, appskey);
    #else
    // If not running an AVR with PROGMEM, just use the arrays directly 
    LMIC_setSession (0x1, DEVADDR, NWKSKEY, APPSKEY);
    #endif

    // Set up the channels used by the Things Network, which corresponds
    // to the defaults of most gateways. Without this, only three base
    // channels from the LoRaWAN specification are used, which certainly
    // works, so it is good for debugging, but can overload those
    // frequencies, so be sure to configure the full frequency range of
    // your network here (unless your network autoconfigures them).
    // Setting up channels should happen after LMIC_setSession, as that
    // configures the minimal channel set.
    
    LMIC_setupChannel(0, 865062500, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
    LMIC_setupChannel(1, 865402500, DR_RANGE_MAP(DR_SF12, DR_SF7B), BAND_CENTI);      // g-band
    LMIC_setupChannel(2, 865985000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI); 
    // TTN defines an additional channel at 869.525Mhz using SF9 for class B
    // devices' ping slots. LMIC does not have an easy way to define set this
    // frequency and support for class B is spotty and untested, so this
    // frequency is not configured here.

    // Disable link check validation
    LMIC_setLinkCheckMode(0);

    // Set data rate and transmit power (note: txpow seems to be ignored by the library)
    LMIC_setDrTxpow(DR_SF7,14);
    display.init();
  display.flipScreenVertically();  
  display.setFont(ArialMT_Plain_10);


    // Start job
    do_send(&sendjob);
}

void loop() {
  
    os_runloop_once();
    



  
}
