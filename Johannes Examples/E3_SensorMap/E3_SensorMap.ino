#include <SoftwareSerial.h>
#include "Adafruit_VL53L0X.h"

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

#define rxPin 8
#define txPin 9
SoftwareSerial mySerial(rxPin, txPin);  // Create the new software serial instance

#define LSS_ID 254 // ID 254 to broadcast to every motor on bus

void setup()
{
  mySerial.begin(115200); // Important! this is the standard speed for talking to LSS
  mySerial.print("#0D1500\r");  // this is used to clear the serial buffer

  Serial.println("Adafruit VL53L0X test");
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while(1);
  }
  // power 
  Serial.println(F("VL53L0X API Simple Ranging example\n\n")); 
}

void loop() {
  int distance = 0;
  int angle = 0;

  VL53L0X_RangingMeasurementData_t measure;
    
  Serial.print("Reading a measurement... ");
  lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!

  if (measure.RangeStatus != 4) {  // phase failures have incorrect data
    distance = measure.RangeMilliMeter;
    Serial.print("Distance (mm): "); Serial.println(measure.RangeMilliMeter);
  } else {
    Serial.println(" out of range ");
  }

  angle = map(distance, 0, 800, 0, 180);

  // Move to specific position in 1/10° (i.e 100 = 10 degrees)
  mySerial.print(String("#") + LSS_ID + String("D") + int(angle*10)  + "\r");
  delay(100);
}