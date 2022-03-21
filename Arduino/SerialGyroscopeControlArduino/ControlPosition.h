
#define PI    3.141594
#define KSI   0.03
#define Gc    1000
#define VREF  0.1
#define WREF  0
#define L     0.2
#define CORRECTIONANGULAR 4

//#define KSI   0.9
//#define G     30

void InitGyroscope();
void updateGyroscope(float * angle);
void updateControlPosition(float * speedMotor1, float * speedMotor2);
