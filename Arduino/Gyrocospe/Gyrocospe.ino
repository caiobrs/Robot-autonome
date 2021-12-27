#include "MeOrion.h"
#include <Wire.h>

MeGyro gyro;
void setup()
{
  Serial.begin(115200);
  gyro.begin();
}

int i = 0;

void loop()
{
  gyro.update();
  

  i++;

  if (i == 100) {
    Serial.print("X:");
    Serial.print(gyro.getAngleX() );
    Serial.print(" Y:");
    Serial.print(gyro.getAngleY() );
    Serial.print(" Z:");
    Serial.println(gyro.getAngleZ() );
    i = 0;
  }
}
