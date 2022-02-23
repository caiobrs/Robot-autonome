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

void loop() {
  // put your main code here, to run repeatedly:
  //setMotorAVoltage1(9);
  //setMotorAVoltage2(6);
  if (StatusKart == 0){

    if(setKartADistance(0.5,5)== 2){

      setKartADistance(0.5,5);
      StatusKart++;

    }
    
    Serial.println(getPosition2());
  }
  
}

int statusMovementKart = 0;
int positionBeginMovement = 0;

int setKartADistance(float distance, float tension) {
  if (statusMovementKart == 0) {
    statusMovementKart = 1;
    positionBeginMovement = getPosition1();
  }
  else if (statusMovementKart == 1) {
    if (abs(getPosition1() - positionBeginMovement) < distance) {
      setMotorAVoltage1(tension);
      setMotorAVoltage2(tension);
    }
    else {
      statusMovementKart = 2;
    }
  }
  else if (statusMovementKart == 2) {
    setMotorAVoltage1(0);
    setMotorAVoltage2(0);
    statusMovementKart = 0;
  }

  return statusMovementKart;
}
