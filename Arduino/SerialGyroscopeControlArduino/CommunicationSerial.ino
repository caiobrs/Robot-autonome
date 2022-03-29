
#define MAXCARACTER 10

char messageReceived[MAXCARACTER];
int indexMessage = -1;
int stateMessage = 0;
//0 - Normal
//1 - Buffer Out

void InitSerial() {
  Serial2.begin(9600);
}

void clearMessage() {
  for (int i = 0; i < MAXCARACTER; i++)
    messageReceived[i] = 0;
}

void updateSerial(int * curPosX, int * curPosY, int * tarPosX, int * tarPosY, float * tarAngle) {
  
  while (Serial2.available()) {
    
    char caracter = Serial2.read();
    
    if (caracter == '#') {
      indexMessage = 0;
      stateMessage = 0;
    }
    else if (caracter == '%') {
      indexMessage = -1;
      
      if (stateMessage == 0) {
        messageReceived[indexMessage] = '\0';
        //Serial.println(messageReceived);
        setVariable(curPosX, curPosY, tarPosX, tarPosY, tarAngle);
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

void setVariable(int * curPosX, int * curPosY, int * tarPosX, int * tarPosY, float * tarAngle){
  if (messageReceived[0] == 'P' || messageReceived[0] == 'T') {
    
    float auxValue = 0;
    
    for (int i = 3; messageReceived[i] != '\0'; i++)
      auxValue = auxValue * 10.0 + messageReceived[i] - '0';

    if (messageReceived[2] == '-')
      auxValue *= -1;
    
    if (messageReceived[0] == 'P') {
      if (messageReceived[1] == 'x')
        (*curPosX) = auxValue;
      else
        (*curPosY) = auxValue;
    }
    else if (messageReceived[0] == 'T') {
      if (messageReceived[1] == 'x')
        (*tarPosX) = auxValue;
      else if (messageReceived[1] == 'y')
        (*tarPosY) = auxValue;
      else
        (*tarAngle) = auxValue;
    }

    //Serial.println(messageReceived);
  }

  clearMessage();
}
