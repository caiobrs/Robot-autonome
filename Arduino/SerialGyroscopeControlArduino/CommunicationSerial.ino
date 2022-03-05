
#define MAXCARACTER 80
#define TIMEWAITING 50

char messageReceived[MAXCARACTER];
int indexMessage = -1;
int stateMessage = 0;
//0 - Normal
//1 - Buffer Out

char messageToRaspberry[100];
int iSendToRaspberry = 0;

int stateCommunication = 0;
//0 - Read
//1 - Write
//2 - Wait TIMEWAITING ms

long lastTimeWaiting;

void InitSerial() {
  Serial2.begin(9600);
}

void updateSerial() {
  
  if (stateCommunication == 0) {
    while (Serial2.available()) {
      
      char caracter = Serial2.read();
      
      if (caracter == '#') {
        indexMessage = 0;
        stateMessage = 0;
      }
      else if (caracter == '%') {
        indexMessage = -1;
        stateCommunication = 1;
        
        if (stateMessage == 0) {
          messageReceived[indexMessage] = '\0';
          Serial.println(messageReceived);
          setVariable();
        }
        
        break;
        
      }
      else if (indexMessage >= 0) {
        
        if (indexMessage == MAXCARACTER) {
          stateMessage = 1;
        }
        else {
          messageReceived[indexMessage] = caracter;
          indexMessage++;
        }
      }
    }
  }
  else if (stateCommunication == 1){
    if (iSendToRaspberry == 1000) {
      Serial2.println(messageToRaspberry);
      iSendToRaspberry = 0;
    }
    else {
      Serial2.println("#%");
    }

    lastTimeWaiting = millis();
    stateCommunication = 2;
  }
  else if (stateCommunication == 2) {
    if (millis() - lastTimeWaiting > TIMEWAITING) {
      stateCommunication = 0;
    }
  }
}

void setVariable(){
  if (messageReceived[0] == 's') {
    float speedMotorDesired = 0;

    for (int i = 3; messageReceived[i] != '\0'; i++)
      speedMotorDesired = speedMotorDesired * 10.0 + messageReceived[i] - '0';

    if (messageReceived[2] == '-')
      speedMotorDesired *= -1;

        
    if (messageReceived[1] == '1') {
      speedMotor1 = speedMotorDesired / 1000.0;
    }
    else if (messageReceived[1] == '2') {
      speedMotor2 = speedMotorDesired / 1000.0;
    }
  }
}

void writeMessageRaspberry(char messageRasp[8]) {

  int i;
  iSendToRaspberry = 1;
  
  for (i = 0; messageRasp[i] != '\0'; i++)
    messageToRaspberry[i] = messageRasp[i];

  messageToRaspberry[i] = '\0';
  
}
