#include "Motors.h"
#include "Encoders.h"
#include "CommunicationSerial.h"

void setup() {
  // put your setup code here, to run once:

  InitMotors();
  InitEncoders();
  Serial2.begin(9600);
  Serial.begin(115200);
}

int StatusKart = 0;

void loop() {
  if (StatusKart == 0) {
    updateSerial();

    char message[8];
    message[0] = '\0';
  
    getMessage(message);
  
    if (message[0] != '\0') {
      Serial.println(message);

      if (message[0] == 'B')
        StatusKart++;
    }
  }
  else if (StatusKart == 1){

    if(setKartADistance(0.5,5)== 2){

      setKartADistance(0.5,5);
      StatusKart++;

    }
  }
  else {
    StatusKart = 0;
  }
  
}

int statusMovementKart = 0;
float positionBeginMovement = 0;

int setKartADistance(float distance, float tension) {
  if (statusMovementKart == 0) {
    statusMovementKart = 1;
    positionBeginMovement = getPosition1();
    Serial.println(getPosition1());
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
    positionBeginMovement = getPosition1();
  }

  return statusMovementKart;
}
