#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN       6
#define NUMPIXELS 8
#define DELAYVAL  500

const char* morseSOS = "...---...";

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
    clock_prescale_set(clock_div_1);
  #endif

  pixels.begin();
}

void loop() {
  for (int i = 0; morseSOS[i]; i++) {
    if (morseSOS[i] == '.') {
      flashLED(); 
      delay(DELAYVAL);
      turnOff();
      delay(DELAYVAL);
    } else if (morseSOS[i] == '-') {
      flashLED(); 
      delay(1000);
      turnOff();
      delay(DELAYVAL);
    }

 
  }
  
  // delay(3 * DELAYVAL);
}

void flashLED() {
        pixels.clear();
  //for (int i = 0; i < count; i++) {
    for (int j = 0; j < NUMPIXELS; j++) {
      pixels.setPixelColor(j, pixels.Color(0, 150, 0)); 
    }
      pixels.show();
}

void turnOff() {
    pixels.clear();
    pixels.show();
}