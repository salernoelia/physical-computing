#include <SoftwareSerial.h>
#include <Wire.h>
#include <LSM6.h>

#define rxPin 8
#define txPin 9
SoftwareSerial mySerial(rxPin, txPin);  // Create the new software serial instance

#define LSS_ID 254 // ID 254 to broadcast to every motor on bus
#define NEW_ID_ONE 1
#define NEW_ID_TWO 2 

// LSM6 imu;

// char report[80];

void setup()
{
  Serial.begin(9600);
  mySerial.begin(115200); // Important! this is the standard speed for talking to LSS
  mySerial.print("#0D1500\r");  // this is used to clear the serial buffer

  // if (!imu.init())
  // {
  //   Serial.println("Failed to detect and initialize IMU!");
  //   while (1);
  // }
  // imu.enableDefault();

  // Setup an individual ID for each Motor
  // mySerial.print(String("#") + LSS_ID + String("CID") + NEW_ID_ONE  + "\r"); // RPM move
  //mySerial.print(String("#") + LSS_ID + String("CID") + NEW_ID_TWO  + "\r"); // RPM move

}

void loop() {
  // imu.read();
  //  snprintf(report, sizeof(report), "A: x:%6d y:%6d z:%6d    G: x:%6d y:%6d z:%6d",
  //   imu.a.x, imu.a.y, imu.a.z,
  //   imu.g.x, imu.g.y, imu.g.z);
  // Serial.println(report);

  

//   // Move the LSS continuously in the oposite direction
  delay(3000);
  mySerial.print(String("#") + NEW_ID_ONE + String("WR") + -30  + "\r"); // RPM move
  delay(3000);
  mySerial.print(String("#") + NEW_ID_TWO + String("WR") + 30  + "\r"); // RPM move
  delay(3000);
  // mySerial.print(String("#") + LSS_ID + String("WR") + 50  + "\r"); // RPM move

  // delay(5000);
//   // faster!
//   mySerial.print(String("#") + LSS_ID + String("WR") + -60  + "\r"); // RPM move
//   delay(3000);
//   // go Limp!
//  mySerial.print(String("#") + LSS_ID + String("L") + "\r"); // Limp
//   delay(5000);
//   // move relative from current position in 1/10° (i.e 100 = 10 degrees)
  // mySerial.print(String("#") + NEW_ID_TWO + String("D") + int(60*10)  + "\r"); // move 100 degrees
//   delay(5000);
//   // Move to specific position in 1/10° (i.e 100 = 10 degrees)
//   mySerial.print(String("#") + LSS_ID + String("D") + int(360*10)  + "\r"); // move 360 degrees
//   delay(7000);
}