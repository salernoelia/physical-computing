const int photoresistorPin = A0; // Analog pin where the photoresistor is connected
#define PIN       6

void setup() {
  Serial.begin(9600); // Initialize serial communication for debugging
}

void loop() {
  // Read the analog value from the photoresistor
  int photoresistorValue = analogRead(photoresistorPin);
  int mappedValue = map(photoresistorValue, 650, 950, LOW, 255);



  // Print the value to the serial monitor
  Serial.print("Photoresistor Value: ");
  Serial.println(mappedValue);


  analogWrite(PIN, mappedValue);

  // Add a short delay for stability
  delay(50);
}
