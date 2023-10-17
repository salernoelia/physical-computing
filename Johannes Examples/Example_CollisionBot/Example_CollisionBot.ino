#include <SoftwareSerial.h>

#define rxPin 8
#define txPin 9
SoftwareSerial mySerial(rxPin, txPin);  // Create the new software serial instance
int incomingByte = 0; // for incoming serial data


#define LSS_ID_R 1 // ID 254 to broadcast to every motor on bus
#define LSS_ID_L 2 // ID 254 to broadcast to every motor on bus

int current = 0;


void setup()
{
  Serial.begin(9600);
  mySerial.begin(115200); // Important! this is the standard speed for talking to LSS
  mySerial.print("#0D1500\r");  // this is used to clear the serial buffer
  mySerial.print(String("#") + LSS_ID_R + String("G-1") + "\r");
  delay(6000);
}

void loop()
{
  checkCurrent();
  if (current > 105) {
    stop();
    delay(500);
    turn();
    delay(3000);
    stop();
    delay(1000);
    return;
  }
  else {
    driveForward();
  }
}

void driveForward() {
  mySerial.print(String("#") + LSS_ID_R + String("WR80") + "\r");
  mySerial.print(String("#") + LSS_ID_L + String("WR80") + "\r");
  //Serial.println("Forward");
}

void turn() {
  mySerial.print(String("#") + LSS_ID_R + String("WR-180") + "\r");
  mySerial.print(String("#") + LSS_ID_L + String("WR-180") + "\r");
  delay(2000);
  mySerial.print(String("#") + LSS_ID_R + String("WR-200") + "\r");
  mySerial.print(String("#") + LSS_ID_L + String("WR200") + "\r");
  //Serial.println("Turn");
}

void stop() {
  mySerial.print(String("#") + LSS_ID_R + String("WR0") + "\r");
  mySerial.print(String("#") + LSS_ID_L + String("WR0") + "\r");
  //Serial.println("Stop");
}

void checkCurrent() {
  mySerial.print(String("#") + LSS_ID_R + String("QC") + "\r");
  String responseString = mySerial.readString();
  char responseArray[8];
  int length = 8;
  responseString.toCharArray(responseArray, length);
  //Serial.println(responseString);
  char query[4];
  char value[3];
  sscanf(responseArray, "%4c%s", query, value);
  current = atoi(value);
  Serial.println(current);
}
