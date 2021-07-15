// http://www.bajdi.com
// Sending a struct with the nRF24L01 module
// Data to be sent is the reading of 2 analog pins
// Data received is the analog reading of 2 pins on the other Arduino 

#include <SoftwareSerial.h>
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

SoftwareSerial kirim(5,6);

int period=500;

typedef struct{
  float W;
  float X;
  float Y;
  float Z;
}
B_t;


B_t duino2;

RF24 radio(9,10);   // make sure this corresponds to the pins you are using
const uint64_t pipes[2] = { 
  0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };

unsigned long time_now = 0;

void setup()
{
  Serial.begin(57600);
  radio.begin();
  radio.openWritingPipe(pipes[1]);
  radio.setPALevel(RF24_PA_MIN);
  radio.openReadingPipe(1,pipes[0]);
  radio.startListening();
  kirim.begin(9600);
}

void loop(void)
{ 
  // we need data to sent...

  // end of analog reading

  // radio stuff
  if ( radio.available() ){  
     radio.read( &duino2, sizeof(duino2) );
     Serial.print("data1:");
     Serial.print(duino2.W);
     Serial.print("\t");
     Serial.print("data2:");
     Serial.print(duino2.X);
     Serial.print("\t");
     Serial.print("data3:");
     Serial.print(duino2.Y);
     Serial.print(" ");
     Serial.print("data4:");
     Serial.println(duino2.Z);
  }

  if((unsigned long)(millis() - time_now)>period){
    time_now = millis();
    
    kirim.println("t#"+ String(duino2.W) + "#" + String(duino2.X) + "#" + String(duino2.Y) );  
    Serial.println("t#"+ String(duino2.W) + "#" + String(duino2.X) + "#" + String(duino2.Y) );  
  }

  
  // end of radio stuff

  // serial print received data 
  
  // end of serial printing
}
