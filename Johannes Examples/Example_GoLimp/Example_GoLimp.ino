#include <SoftwareSerial.h>

#define rxPin 8
#define txPin 9
SoftwareSerial mySerial(rxPin, txPin);  // Create the new software serial instance

#define LSS_ID 2


void setup()
{
  Serial.begin(9600);
  mySerial.begin(115200); // Important! this is the standard speed for talking to LSS
  mySerial.print("#0D1500\r");  // this is used to clear the serial buffer
  delay(1000);
}

void loop()
{
  mySerial.print(String("#") + LSS_ID + String("WR60CL110") + "\r");
}
