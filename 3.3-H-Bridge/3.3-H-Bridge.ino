const int motorInput1 = 5;  // Connect to pin 5 on Arduino
const int motorInput2 = 6;  // Connect to pin 6 on Arduino
const int toggle = 7; 
int speed = 150;  // Motor speed (0 to 255)
const int motorSpeedPin = 9;  // Connect to an appropriate PWM pin on Arduino


void setup() {
  Serial.begin(9600);
  pinMode(motorInput1, OUTPUT);
  pinMode(motorInput2, OUTPUT);
  pinMode(toggle, INPUT);
}

void loop() {

  int togglesw = digitalRead(toggle);
  // Serial.println(togglesw);

  // if (togglesw == LOW) {
  //   Serial.println("works");
  // }
  // Move the motor forward
  motorForward();
  delay(2000);  // Move forward for 2 seconds
  
  // Stop the motor
  motorStop();
  delay(1000);  // Stop for 1 second

  // Move the motor backward
  motorBackward();
  delay(2000);  // Move backward for 2 seconds
  
  // Stop the motor
  motorStop();
  delay(1000);  // Stop for 1 second
}

void motorForward() {
  digitalWrite(motorInput1, HIGH);
  digitalWrite(motorInput2, LOW);
  analogWrite(motorSpeedPin, speed); // Set motor speed
}

void motorBackward() {
  digitalWrite(motorInput1, LOW);
  digitalWrite(motorInput2, HIGH);
  analogWrite(motorSpeedPin, speed); // Set motor speed
}

void motorStop() {
  digitalWrite(motorInput1, LOW);
  digitalWrite(motorInput2, LOW);
  analogWrite(motorSpeedPin, 0);  // Stop the motor
}
