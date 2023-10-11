const int ledPin = 9; // Choose a PWM-capable pin
int brightness = 0;  // Set initial brightness value

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Increase brightness gradually
  for (brightness = 0; brightness <= 255; brightness += 5) {
    analogWrite(ledPin, brightness);
    delay(10); // Adjust the delay for the desired fade speed
  }
  
  // Decrease brightness gradually
  for (brightness = 255; brightness >= 0; brightness -= 5) {
    analogWrite(ledPin, brightness);
    delay(10); // Adjust the delay for the desired fade speed
  }
}

