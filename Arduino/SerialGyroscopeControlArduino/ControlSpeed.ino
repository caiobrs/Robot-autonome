#include "ControlSpeed.h"

#define nMotor 2

const float maxVoltage = 9.0;
const float Kp = 0.3;
const float Ki = 2.6;

float sumError[nMotor];

int sign(float value) {
  return int((value>0)-(value<0));
}

float convertSpeedToTension(float speedValue) {
  return (1.039223301 + 28.83495146 * speedValue);
}

float updateControlSpeed(float desiredSpeed, float currentSpeed, int motor){
  
  if (desiredSpeed == 0.0)
    return 0;
    
  motor--;
  float error = desiredSpeed - currentSpeed;
  
  float tension = sumError[motor] * Ki * DT / 1000.0 + error * Kp;
  tension = convertSpeedToTension(tension);

  if (sign(error) != sign(tension) || tension < maxVoltage)
    sumError[motor] += error;

  return tension;
}
