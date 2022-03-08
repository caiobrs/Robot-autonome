
#define PI    3.141594
#define KSI   0.9
#define G     30
#define VREF  0.1
#define WREF  0
#define L     0.2

void InitGyroscope();
void updateGyroscope();
void updateControlPosition(float * speedMotor1, float * speedMotor2);
