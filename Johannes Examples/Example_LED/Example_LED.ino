#include <SoftwareSerial.h>

#define rxPin 8
#define txPin 9
SoftwareSerial mySerial(rxPin, txPin);  // Create the new software serial instance

#define LSS_ID 254 // ID 254 to broadcast to every motor on bus


void setup()
{
  Serial.begin(9600);
  mySerial.begin(115200); // Important! this is the standard speed for talking to LSS
  mySerial.print("#0D1500\r");  // this is used to clear the serial buffer
}

void loop()
{
	// Loop through 8 LED colors
	for (int LEDCode = 0; LEDCode <= 7; LEDCode++){
	// Set the color (session only) of the LSS
    // Options are:
    // LSS_LED_Black = 0
    // LSS_LED_Red = 1
    // LSS_LED_Green = 2
    // LSS_LED_Blue = 3
    // LSS_LED_Yellow = 4
    // LSS_LED_Cyan = 5
    // LSS_LED_Magenta = 6
    // LSS_LED_White = 7
	  mySerial.print(String("#") + LSS_ID + String("LED") + LEDCode + "\r"); // set LED
	 delay(1000);
	}
}
