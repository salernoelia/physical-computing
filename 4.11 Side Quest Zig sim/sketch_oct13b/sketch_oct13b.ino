int motorPin = 9; 

int motorSpeed; // Variable to store speed value 

void setup() {

  Serial.begin(9600); // Initialize serial

  pinMode(motorPin, OUTPUT); // Set motor pin as output

}

void loop() {

  if(Serial.available() > 0) { // Check for serial input

    motorSpeed = Serial.parseInt(); // Read speed value as integer

    motorSpeed = constrain(motorSpeed, 0, 255); // Constrain value to 0-255

    analogWrite(motorPin, motorSpeed); // Write PWM value    

    Serial.println(motorSpeed);

  }

}