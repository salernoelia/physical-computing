#include <Adafruit_NeoPixel.h>

const int power = 7;
int Ain = 12;
int Bin = 13;

int Apoints = 0;
int Bpoints = 0;

int AwonPin = 2;
int BwonPin = 4;


#define PIN 8
#define NUMPIXELS 8

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(57600);
  pinMode(Ain, INPUT);
  pinMode(Bin, INPUT);
  pinMode(power, OUTPUT);
  pinMode(AwonPin, OUTPUT);
  pinMode(BwonPin, OUTPUT);
  pinMode(PIN, OUTPUT);
  pixels.begin();
  digitalWrite(power, HIGH);
}

void loop() {

  //A Player / Green
  for (int i = 0; i <= NUMPIXELS; i++) {
    int oldAval = digitalRead(Ain);
    pixels.clear();
    pixels.setPixelColor(i, pixels.Color(0, 25, 0));
    pixels.show();
    delay(random(80, 150));

    int Aval = digitalRead(Ain);

    if (Aval == HIGH && oldAval == LOW && i == 0) {
      Apoints++;
      Serial.print(Apoints);
      Serial.print("," );
      Serial.println(Bpoints);
      delay(250);
    }
  }

  //B Player / Red
  for (int i = NUMPIXELS - 1; i >= 0; i--) {

    int oldBVal = digitalRead(Bin);
    pixels.clear();
    pixels.setPixelColor(i, pixels.Color(25, 0, 0));
    pixels.show();
    delay(random(80, 150));

    int Bval = digitalRead(Bin);

    if (Bval == HIGH && oldBVal == LOW && i == 7) {
      Bpoints++;
      Serial.print(Apoints);
      Serial.print(",");
      Serial.println(Bpoints);
      delay(250);
    }
  }
  if (Apoints >= 10) {

    digitalWrite(AwonPin, HIGH);
  }
  if (Bpoints >= 10) {

    digitalWrite(BwonPin, HIGH);
  }

 
 

}
