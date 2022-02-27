#include "Motors.h"
#include "Encoders.h"
#include "ControlSpeed.h"
#include "CommunicationSerial.h"

#define DT 5

long lastTime = 0;
float speedMotor1 = 0;
float speedMotor2 = 0;

void setup() {
  // put your setup code here, to run once:

  InitMotors();
  InitEncoders();
  InitSerial();

  lastTime = millis();

  writeMessageRaspberry("Batata");

}

int index = 0;

void loop() {

    while(millis() - lastTime > DT) 
      lastTime = millis();

    updateSerial();

    float tensionMotor1 = updateControl(speedMotor1, getSpeedMotor1(), 1);
    float tensionMotor2 = updateControl(speedMotor2, getSpeedMotor2(), 2);

    setMotorAVoltage1(tensionMotor1);
    setMotorAVoltage2(tensionMotor2);
}
