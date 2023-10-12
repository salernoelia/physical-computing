#include <Adafruit_NeoPixel.h>

 
const int power = 7;

 int Ain = 12;
 int Bin = 13;

int Aval = digitalRead(Ain);
int Bval = digitalRead(Bin);

#define PIN        8
#define NUMPIXELS 8 // Popular NeoPixel ring size


Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  
  pinMode(Ain, INPUT);
  pinMode(Bin, INPUT);
  pinMode(power, OUTPUT);
  pinMode(PIN, OUTPUT);
  pixels.begin();
  digitalWrite(power, HIGH);
}

void loop() {
  
 
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.clear();
    pixels.setPixelColor(i, pixels.Color(0, 25, 0));
    pixels.show();
    delay(random(10,200));
    
  }

  for (int i = NUMPIXELS - 1; i >= 0; i--) {
    pixels.clear();
    pixels.setPixelColor(i, pixels.Color(25, 0, 0));
    pixels.show();
    delay(random(10,200));
  }

  if (Aval == HIGH) {
    Serial.println("detected");
  }

}
