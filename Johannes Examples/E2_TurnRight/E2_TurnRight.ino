#include <SoftwareSerial.h>

#define rxPin 8
#define txPin 9
SoftwareSerial mySerial(rxPin, txPin);  // Create the new software serial instance

#define LSS_ID_R 1 
#define LSS_ID_L 2 


void setup()
{
  Serial.begin(9600);
  mySerial.begin(115200); // Important! this is the standard speed for talking to LSS
  mySerial.print("#0D1500\r");  // this is used to clear the serial buffer
  delay(2000);
}

void loop()
{
  drive();
  delay(10000);
  turn();
  delay(2000);
}

void turn() {
  String actionR = "MD";
  String valueR = "20000";
  String actionL = "WR";
  String valueL = "0";

  mySerial.print(String("#") + LSS_ID_R + actionR + valueR + "\r");
  mySerial.print(String("#") + LSS_ID_L + actionL + valueL + "\r");
}

void drive() {
  String actionR = "WR";
  String valueR = "20";
  String actionL = "WR";
  String valueL = "-20";

  mySerial.print(String("#") + LSS_ID_R + actionR + valueR + "\r");
  mySerial.print(String("#") + LSS_ID_L + actionL + valueL + "\r");
}
