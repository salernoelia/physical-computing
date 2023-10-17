#include <SoftwareSerial.h>

#define rxPin 8
#define txPin 9
SoftwareSerial mySerial(rxPin, txPin);  // Create the new software serial instance

#define LSS_ID 254 // ID 254 to broadcast to every motor on bus

void setup()
{
  mySerial.begin(115200); // Important! this is the standard speed for talking to LSS
  mySerial.print("#0D1500\r");  // this is used to clear the serial buffer
}

void loop() {
  // Move the LSS continuously in one direction
  mySerial.print(String("#") + LSS_ID + String("WR") + "20"  + "\r"); // WR: Wheele Mode in RPM
  delay(10000);
  // Move the LSS continuously in the oposite direction
  mySerial.print(String("#") + LSS_ID + String("WR") + "-20"  + "\r"); // WR: Wheele Mode in RPM
  delay(10000);
}