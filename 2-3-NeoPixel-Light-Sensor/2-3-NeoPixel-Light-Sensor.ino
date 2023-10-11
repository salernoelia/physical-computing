// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library

#include <Adafruit_NeoPixel.h>

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        6 // On Trinket or Gemma, suggest changing this to 1
const int photoresistorPin = A0; // Analog pin where the photoresistor is connected

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 8 // Popular NeoPixel ring size



// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 50 // Time (in milliseconds) to pause between pixels

void setup() {
  Serial.begin(9600);
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
}

void loop() {
  pixels.clear(); // Set all pixel colors to 'off'

  int photoresistorValue = analogRead(photoresistorPin);
  int mappedValue = map(photoresistorValue, 650, 800, 0, 8);
	int constrainedValue = constrain(mappedValue, -1, 9);


  // Print the value to the serial monitor
  Serial.println(constrainedValue);

  // The first NeoPixel in a strand is #0, second is 1, all the way up
  // to the count of pixels minus one.
  for(int i=0; i<constrainedValue; i++) { // For each pixel...


    // Here we're using a moderately bright green color:
    pixels.setPixelColor(i, pixels.Color(0,50,0));

   
  }
   pixels.show();   // Send the updated pixel colors to the hardware, needs to be only once in the code

    delay(DELAYVAL); // Pause before next pass through loop
}
