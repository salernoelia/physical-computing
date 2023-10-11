const int switchPin = 7;
const int ledPin = 13;
int switchState = LOW;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(switchPin, INPUT);
}

void loop() {
  int newSwitchState = digitalRead(switchPin);
  
  if (newSwitchState != switchState) {
    switchState = newSwitchState;

    if (newSwitchState = switchState) {
      digitalWrite(ledPin, !digitalRead(ledPin));
    }
  }
}
