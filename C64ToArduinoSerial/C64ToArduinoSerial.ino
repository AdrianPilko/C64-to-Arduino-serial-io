#include <SoftwareSerial.h>

SoftwareSerial  c64Serial(11,10);


void setup() 
{  
  Serial.begin(1200);
  while(!Serial)
  {
    // wait for serial connection to PC (over USB)
  }

  Serial.println("connecting to C64...");
  c64Serial.begin(1200);
  // Send a message on connection
  c64Serial.println("HELLO C64 WORLD!");  
}

void loop() {
  // run continously checking for data at either end and write if there is any
  if (c64Serial.available())
  {
    Serial.write(c64Serial.read());
  }
  if(Serial.available())
  {
    c64Serial.write(Serial.read());
  }
}
