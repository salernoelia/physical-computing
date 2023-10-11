const int motorPWM = 9; 
const int motorDirection = 8;

void setup() {
  pinMode(motorPWM, OUTPUT);
  pinMode(motorDirection, OUTPUT);
}

void loop() {
  // Forward motion
  digitalWrite(motorDirection, HIGH); 
  analogWrite(motorPWM, 160); 

  delay(200); // Run for 2 seconds
  
  // Stop the motor
  digitalWrite(motorPWM, LOW);
  
  delay(100); 

  digitalWrite(motorDirection, LOW); // Reverse the direction
  analogWrite(motorPWM, 200); //speed

  delay(20); 
  

  digitalWrite(motorPWM, LOW);
  
  delay(100); /