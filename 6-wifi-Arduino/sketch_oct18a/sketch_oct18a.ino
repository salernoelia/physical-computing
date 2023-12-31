#include <ArduinoBLE.h>
#include <Arduino_LSM6DS3.h> // the IMU used on the Uno Wifi rev 2

BLEService arduinoBleService("C2575D0E-959F-489E-A917-F5778E802EBA"); // create service

// create characteristics and allow remote device to read and write
BLEBoolCharacteristic LEDCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);
BLECharacteristic accelerationCharacteristic ("19B10014-E8F2-537E-4F6C-D104768A1214", BLENotify, sizeof(float) * 3);

void setup() {
  Serial.begin(9600);
  delay(100);
  // begin initialization 
  if (!BLE.begin()) {
    Serial.println("starting BLE failed!");
    while (1);
  }

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }

  // set the local name peripheral advertises
  BLE.setLocalName("arduinoBLEdemo");
  // set the UUID for the service this peripheral advertises:
  BLE.setAdvertisedService(arduinoBleService);
  
  // add the characteristics to the service
  arduinoBleService.addCharacteristic(LEDCharacteristic);
  arduinoBleService.addCharacteristic(accelerationCharacteristic);

  // add the service
  BLE.addService(arduinoBleService);

  // start advertising
  BLE.advertise();

  Serial.println("Bluetooth device active, waiting for connections...");

  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // listen for BLE peripherals to connect:
  BLEDevice central = BLE.central();
  // if a central is connected to peripheral:
  if (central) {
    Serial.print("Connected to central: ");
    // print the central MAC address:
    Serial.println(central.address());
    // while the central is still connected to peripheral:

    while (central.connected()) {
      // note: we will stay in this loop as long as we are connected via BLE!
      if (LEDCharacteristic.written()) {
        bool newValue;
        newValue = LEDCharacteristic.value();
        Serial.print("LED : ");
        Serial.println(newValue);
        digitalWrite(LED_BUILTIN, newValue);
      }
      // code for making the IMU data available over bluetooth
      if (accelerationCharacteristic.subscribed() && IMU.accelerationAvailable()) {
        float acceleration[3];
        // x, y, z
        IMU.readAcceleration(acceleration[0], acceleration[1], acceleration[2]);
        accelerationCharacteristic.writeValue(acceleration, sizeof(acceleration));
      }
    }
  }
}