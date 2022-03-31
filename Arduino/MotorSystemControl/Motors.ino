#include "Motors.h"

void InitMotors()
{
  pinMode(PORT1_BI1,OUTPUT);
  pinMode(PORT1_BI2,OUTPUT);
  pinMode(PORT1_PWM,OUTPUT);

  pinMode(PORT2_BI1,OUTPUT);
  pinMode(PORT2_BI2,OUTPUT);
  pinMode(PORT2_PWM,OUTPUT);
}


// fonction permettant de gerer l'alimentation moteur (sens et amplitude)
void setMotorAVoltage1(float value)
{
  value = -value * VOLT_TO_PWM;
  if(value<0)
  {
    digitalWrite(PORT1_BI1,1);
    digitalWrite(PORT1_BI2,0);
  }
  else
   {
    digitalWrite(PORT1_BI1,0);
    digitalWrite(PORT1_BI2,1);
  }
  analogWrite(PORT1_PWM,constrain(abs(value),0,MAXPWM));
}

void setMotorAVoltage2(float value)
{
  value = value * VOLT_TO_PWM;
  if(value<0)
  {
    digitalWrite(PORT2_BI1,1);
    digitalWrite(PORT2_BI2,0);
  }
  else
   {
    digitalWrite(PORT2_BI1,0);
    digitalWrite(PORT2_BI2,1);
  }
  analogWrite(PORT2_PWM,constrain(abs(value),0,MAXPWM));
}
