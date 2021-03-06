// PIN utilisées pour l'alimentation moteur
#define PORT1_PWM 12
#define PORT1_BI1 35
#define PORT1_BI2 34

#define PORT2_PWM 8
#define PORT2_BI1 36
#define PORT2_BI2 37

#define MAXPWM 130 // maximum duty cycle for the PWM is 255/MAXPWM
#define VOLT_TO_PWM 255.0/12.0

void InitMotors();
void setMotorAVoltage1(float value);
void setMotorAVoltage2(float value);
