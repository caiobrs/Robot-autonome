#include "Motors.h"
#include "Encoders.h"
#include "ControlSpeed.h"
#include "CommunicationSerial.h"
#include "ControlPosition.h"

#define DT 5

long lastTime = 0;

int currentPositionX = 0;       //mm
int currentPositionY = 0;       //mm
float currentPositionAngle = 0; //degrees

int targetPositionX = 0;        //mm
int targetPositionY = 0;        //mm
float targetPositionAngle = 0;  //degrees

float speedMotor1 = 0;
float speedMotor2 = 0;

float tensionMotor1 = 0;
float tensionMotor2 = 0;

void setup() {
  // put your setup code here, to run once:

  InitMotors();
  InitEncoders();
  InitSerial();
  InitGyroscope();

  lastTime = millis();

  Serial.begin(9600);
}

int teste = 0;
int indexTest = 0;

void loop() {

  while(millis() - lastTime < DT) {}
  
  lastTime = millis();
  indexTest++;
  
  updateGyroscope(&currentPositionAngle);
  updateSerial(&currentPositionX, &currentPositionY, &targetPositionX, &targetPositionY, &targetPositionAngle);
  updateControlPosition(&speedMotor1, &speedMotor2);

  tensionMotor1 = updateControlSpeed(speedMotor1, getSpeedMotor1(), 1);
  tensionMotor2 = updateControlSpeed(speedMotor2, getSpeedMotor2(), 2);

  setMotorAVoltage1(tensionMotor1);
  setMotorAVoltage2(tensionMotor2);
  
}
