#include "ControlPosition.h"
#include "MeOrion.h"
#include <Wire.h>

MeGyro gyro;

void InitGyroscope() {
  gyro.begin();
}

void updateGyroscope(float * angle) {
  gyro.update();

  (*angle) = gyro.getAngleZ();
}

int i = 0;
void updateControlPosition(float * speedMotor1, float * speedMotor2) {

  i++;
  if (i < 26) {
    return;
  }
  i = 0;
  
  //-----------------------------------------------------------------------------
  //--------------------------------Error Calcul---------------------------------
  //-----------------------------------------------------------------------------
  
  float positionX = currentPositionX / 1000.0;
  float positionY = currentPositionY / 1000.0;
  float positionAngle = currentPositionAngle * 2 * PI / 360.0;
  
  float targetX = targetPositionX / 1000.0;
  float targetY = targetPositionY / 1000.0;
  float targetAngle = targetPositionAngle * 2 * PI / 360.0;

  float errorX = targetX - positionX;
  float errorY = targetY - positionY;

  Serial.print(positionX);
  Serial.print(", ");
  Serial.print(positionY);
  Serial.print(", ");
  Serial.print(positionAngle);
  Serial.print(", ");
  Serial.print(targetX);
  Serial.print(", ");
  Serial.print(targetY);
  Serial.print(", ");
  Serial.println(targetAngle);
  
  float errorTheta = targetAngle - positionAngle;
  double errorOne = 0;
  double errorTwo = 0;
  
  if (sqrt(errorX * errorX + errorY * errorY) < 0.20) {
    (*speedMotor1) = 0;
    (*speedMotor2) = 0;
    return;
  }

  double sinCurrentTheta = sin(positionAngle);
  double cosCurrentTheta = cos(positionAngle);

  errorOne = errorX * cosCurrentTheta + errorY * sinCurrentTheta;
  errorTwo = errorY * cosCurrentTheta - errorX * sinCurrentTheta;

  //-----------------------------------------------------------------------------
  //---------------------------------Controller----------------------------------
  //-----------------------------------------------------------------------------

  float v[2] = {0.0, 0.0};
  float u[2] = {0.0, 0.0};

  float wn = sqrt(WREF * WREF + Gc * VREF * VREF);

  float k1 = 2 * KSI * wn;
  float k2 = Gc * abs(VREF);
  float k3 = k1;

  v[0] = - k1 * errorOne;
  v[1] = - sign(VREF) * k2 * errorTwo - k3 *  errorTheta;

  u[0] = VREF * cos(errorTheta);
  u[1] = WREF;

  float velocityLinear = u[0] - v[0];
  float velocityAngular = u[1] - v[1];

  //-----------------------------------------------------------------------------
  //------------------------------Convert Velocity-------------------------------
  //-----------------------------------------------------------------------------

  (*speedMotor1) = velocityLinear - L * velocityAngular * CORRECTIONANGULAR / 2.0;
  (*speedMotor2) = velocityLinear + L * velocityAngular * CORRECTIONANGULAR / 2.0;
  
  Serial.print(", ");
  Serial.print((*speedMotor1));
  Serial.print(", ");
  Serial.println((*speedMotor2));
}
