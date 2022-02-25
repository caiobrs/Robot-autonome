#include "Motors.h"
#include "Encoders.h"

void setup() {
  // put your setup code here, to run once:

  InitMotors();
  InitEncoders();
  Serial.begin(9600);
  delay(2000);
}

int StatusKart = 0;
float sum = 0.0;
int index = 0;

void loop() {
  setMotorAVitesse(0.1);

  index++;
  if (index >= 1000) {
    index = 0;
    Serial.println(sum/100.0);
    
    sum = 0;
  }
  
  sum += getSpeedMotor2();
  delay(3);
}

void setMotorAVitesse(float vitesse) {
  setMotorAVoltage2(0);
}
