#include <SoftwareSerial.h>

#define rxPin 8
#define txPin 9
SoftwareSerial mySerial(rxPin, txPin);  // Create the new software serial instance

#define LSS_ID 254 // ID 254 to broadcast to every motor on bus
#define NEW_ID 1


void setup()
{
  Serial.begin(9600);
  mySerial.begin(115200); // Important! this is the standard speed for talking to LSS
  mySerial.print("#0D1500\r");  // this is used to clear the serial buffer

  mySerial.print(String("#") + LSS_ID + String("CID") + NEW_ID + "\r");
  delay(1000);
  mySerial.print(String("#254") + String("RESET") + "\r");
  delay(100);
}

void loop() {

}