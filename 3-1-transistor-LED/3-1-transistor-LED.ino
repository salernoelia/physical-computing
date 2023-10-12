const int transistorPin = 6;  // Pin connected to the base of the transistor

void setup() {
  pinMode(transistorPin, OUTPUT);
}

void loop() {
  // Turn the transistor on (activate) for a few seconds
  analogWrite(transistorPin, 200);
  delay(500);  // Keep it on for 2 seconds

  // Turn the transistor off (deactivate)
  analogWrite(transistorPin, 0);
  delay(500);  // Keep it off for 2 seconds
}
