#include <SoftwareSerial.h>

SoftwareSerial  c64Serial(11,10);

void writeStringToC64WithDelay(String Str, int delayBetweenCharMSec)
{
  for (int currentCharIndex = 0; currentCharIndex < Str.length(); currentCharIndex++)
  {
    c64Serial.write( Str [ currentCharIndex ] );
    delay(delayBetweenCharMSec);
  }  
  c64Serial.write((char)13); // put new line out to c64 
}

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
  c64Serial.write((char)147);  // control code for c64 to clear screen and place cursor at top left
  writeStringToC64WithDelay("ARDUINO TO COMMODORE 64 SERIAL",2);
  writeStringToC64WithDelay("==============================",2);
  writeStringToC64WithDelay("CONNECT TO USB WITH 1200 8N1",2);    
}

void loop() 
{
  while (1)
  {
    // run continously checking for data at either end and write if there is any
    if (c64Serial.available())
    {
      char inputBuffer = c64Serial.read();
      // check the contents for special characters that need converting from PETSCII
      switch ((unsigned)inputBuffer)
      {
          case 13: Serial.write("\n\r"); break; // the character code for line feed and carridge return so print a \n\r
          case 20: Serial.write("\b \b"); break; // the character code for delete
          default:  Serial.write(inputBuffer); // default to writing normally
          break;    
      }
      
    }
    
    if(Serial.available())
    {
      // read character into buffer so it can be echo'd to the local terminal
      char serialBuffer = Serial.read(); 

      switch ((unsigned)serialBuffer)
      {
         
         case '\r' :  Serial.println(""); c64Serial.println(""); break;
               
         default:
              // convert the character to upper case, works better on c64 due to PETSCII character
              if ((serialBuffer > 96) && (serialBuffer < 123)) serialBuffer = serialBuffer - 32;  
             
              // write the character to the commodore 64
              c64Serial.write(serialBuffer);        
              // write the character to the USB serial connection (eg using PuTTY)
              Serial.write((unsigned)serialBuffer);
              break;         
      }
    }
  }
}
