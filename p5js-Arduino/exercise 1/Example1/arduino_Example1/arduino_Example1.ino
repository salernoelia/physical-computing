#define NUM_VALUES 1
// #define OUTPUT_PIN 6

#include <Servo.h>

Servo myservo;  // create servo object to control a servo

int incomingValues[NUM_VALUES];
const int DELAY_MS = 50;

int pos = 0;

void setup() {
  Serial.begin(9600);
  // pinMode(OUTPUT_PIN, OUTPUT);
  myservo.attach(6);
}

void loop() {
  // Check to see if there is any incoming serial data
  if (Serial.available() > 0) {

    
    // read string until the end of the line
    String rcvdSerialData = Serial.readStringUntil('\n');
    // set the output value of PWM pin
    int ouputValue = rcvdSerialData.toInt();
    // analogWrite(OUTPUT_PIN, ouputValue);
    // Serial.println(ouputValue); 
    // in steps of 1 degree
    myservo.write(ouputValue);              // tell servo to go to position in variable 'pos'
    // delay(15);                       // waits 15ms for the servo to reach the position


  
    // myservo.write(ouputValue);
  }
  
  delay(DELAY_MS);
}