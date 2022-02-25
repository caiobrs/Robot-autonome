#include "Motors.h"
#include "Encoders.h"

#include "EEPROM.h"

long tempInit;

void setup() {
  // put your setup code here, to run once:

  InitMotors();
  InitEncoders();
  Serial.begin(9600);
  delay(5000);

  tempInit = micros();
  setMotorAVitesse(0.1);
}

int index = 0;

void loop() {
  //Serial.print(micros() - tempInit);
  //Serial.print("\t");
  //Serial.println(getSpeedMotor2() * 1000.0);


  if (index < 1300) {
    int vitesse = getSpeedMotor2() * 1000.0;
    EEPROM.write(index, vitesse);
    index++;
  }
  else {
    long tempFin = micros();
    Serial.println(tempFin - tempInit);
    setMotorAVitesse(0);
  }
    
}

void setMotorAVitesse(float vitesse) {
  float tension = 1.039223301 + 28.83495146 * vitesse;

  if (vitesse == 0) {
    setMotorAVoltage2(0);
    return;
  }
    
  setMotorAVoltage2(tension);
}
