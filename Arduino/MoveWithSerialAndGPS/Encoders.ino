#include "Encoders.h"

volatile int position1 = 0;
volatile long duration1 = 0;
volatile long timeOfLastPulse1 = 0;
volatile char dir1 = 0;

volatile int position2 = 0;
volatile long duration2 = 0;
volatile long timeOfLastPulse2 = 0;
volatile char dir2 = 0;

float getPosition1()
{
  noInterrupts();
  float temp = position1*(2*3.1415*(28.85))/(380*1000.0);
  interrupts();
  return temp;
}

float getPosition2()
{
  noInterrupts();
  float temp = position2*(2*3.1415*(28.85))/(380*1000.0);
  interrupts();
  return temp;
}

// get the actual speed, computed from the time between two pulses.
float getSpeedMotor1(){
  noInterrupts();
  long tempDur = duration1;
  char tempDir = dir1; 
  interrupts();
  if(tempDur == 0)
    return 0;
  else 
    if(tempDir>0){
      float rot = 1000000.0/( (float)tempDur );
      float v = rot*(2*3.1415*(28.85+4.5))/(8*46);  // Number of pulses per rotation: 8; Gear Ratio : 46; Gear radius: 28.85; Track thickness: 4.5    
      return v;
      }
    else{ 
      float rot = 1000000.0/( (float)tempDur );
      float v = rot*(2*3.1415*(28.85+4.5))/(8*46);
      return -v;
      }
    
}

float getSpeedMotor2(){
  noInterrupts();
  long tempDur = duration2;
  char tempDir = dir2; 
  interrupts();
  if(tempDur == 0)
    return 0;
  else 
    if(tempDir>0){
      float rot = 1000000.0/( (float)tempDur );
      float v = rot*(2*3.1415*(28.85+4.5))/(8*46);  // Number of pulses per rotation: 8; Gear Ratio : 46; Gear radius: 28.85; Track thickness: 4.5    
      return v;
      }
    else{ 
      float rot = 1000000.0/( (float)tempDur );
      float v = rot*(2*3.1415*(28.85+4.5))/(8*46);
      return -v;
      }
    
}


void InitEncoders()
{ 
  pinMode(PORT1_NE2,INPUT_PULLUP);
  pinMode(PORT1_NE1,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PORT1_NE2),ISR_encoder1,RISING);

  pinMode(PORT2_NE2,INPUT_PULLUP);
  pinMode(PORT2_NE1,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PORT2_NE2),ISR_encoder2,RISING);
 
}


// fonction appelée lors des interruptions 'front montant'
void ISR_encoder1(){
  long newTime = micros();
  if(digitalRead(PORT1_NE1)) // detection du sens de rotation
    {
      position1++;
      dir1 = 1;
    }
    else
    {
      position1--;
      dir1 = -1;
    }
  duration1 = newTime - timeOfLastPulse1;
  timeOfLastPulse1 = newTime;
}

void ISR_encoder2(){
  long newTime = micros();
  if(digitalRead(PORT2_NE1)) // detection du sens de rotation
    {
      position2++;
      dir2 = 1;
    }
    else
    {
      position2--;
      dir2 = -1;
    }
  duration2 = newTime - timeOfLastPulse2;
  timeOfLastPulse2 = newTime;
}
