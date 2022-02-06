#include <SoftwareSerial.h>

SoftwareSerial  c64Serial(11,10);


void setup() 
{  
  Serial.begin(1200);
  while(!Serial)
  {
    // wait for serial connection to PC (over USB)
  }

  Serial.println("connecting to C64, 1200baud 8N1");
  c64Serial.begin(1200);
  
  // Send a message on connection
  c64Serial.println("");  
  c64Serial.println("ARDUINO TO COMMODORE 64 SERIAL");    
  c64Serial.println("");  
}

void loop() 
{
  while (1)
  {
    // run continously checking for data at either end and write if there is any
    if (c64Serial.available())
    {
      char inputBuffer = c64Serial.read();
      // check the contents for special characters that need convertiong from PETSCII
      switch ((unsigned)inputBuffer)
      {
          case 13: Serial.write("\n\r"); break; // the character code for line feed and carridge return so print a \n\r
          case 20: Serial.write("\b \b"); break; // the character code for line feed and carridge return so print a \n\r
          default:  Serial.write(inputBuffer); // default to writing normally
          break;    
      }
      
    }
    
    if(Serial.available())
    {
      // read character into buffer so it can be echo'd to the local terminal
      char serialBuffer = Serial.read(); 
  
      // write the character to the commodore 64
      c64Serial.write(serialBuffer);
      
      // write the character to the USB serial connection (eg using PuTTY)
      Serial.write(serialBuffer);
    }
  }
}
