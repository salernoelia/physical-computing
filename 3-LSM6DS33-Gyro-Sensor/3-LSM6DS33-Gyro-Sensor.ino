/*
The sensor outputs provided by the library are the raw
16-bit values obtained by concatenating the 8-bit high and
low accelerometer and gyro data registers. They can be
converted to units of g and dps (degrees per second) using
the conversion factors specified in the datasheet for your
particular device and full scale setting (gain).

Example: An LSM6DS33 gives an accelerometer Z axis reading
of 16276 with its default full scale setting of +/- 2 g. The
LA_So specification in the LSM6DS33 datasheet (page 15)
states a conversion factor of 0.061 mg/LSB (least
significant bit) at this FS setting, so the raw reading of
16276 corresponds to 16276 * 0.061 = 992.8 mg = 0.9928 g.
*/

#include <Wire.h>
#include <LSM6.h>
const int LED = 7;

LSM6 imu;

char report[80];

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  pinMode(LED, OUTPUT);

  if (!imu.init())
  {
    Serial.println("Failed to detect and initialize IMU!");
    while (1);
  }
  imu.enableDefault();
}

void loop()
{
  imu.read();
  int x = imu.g.x;
  int y = imu.g.y;
  int z = imu.g.z;

  int mappedX = map(y, -1000, 0, 0, 100);




  if (imu.a.z < 0) {
Serial.println("upside down");
  digitalWrite(LED, HIGH);
  } else {
  digitalWrite(LED, LOW);
  }

  snprintf(report, sizeof(report), "G: x:%6d y:%6d z:%6d",
    x, y, z);
  Serial.println(report);

  delay(100);
}
