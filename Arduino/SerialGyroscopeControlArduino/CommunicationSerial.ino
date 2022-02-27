
char messageReceived[8];
int indexMessage = -1;

char messageToRaspberry[8];
int iSendToRaspberry = 0;

void InitSerial() {
  Serial2.begin(115200);
}

void updateSerial() {
  if (Serial2.available()) {
    char caracter = Serial2.read();
    
    if (caracter == '#') {
      indexMessage = -1;
    }
    else if (caracter == '%') {
      messageReceived[indexMessage] = '\0';
      setVariable();
      
      indexMessage = -2;
    }
    else 
      messageReceived[indexMessage] = caracter;

    if (indexMessage == 8)
      indexMessage = 0;
    else 
      indexMessage++;
  }
  else if (iSendToRaspberry == 1 && indexMessage == -1) {
    Serial2.print(messageToRaspberry);
    iSendToRaspberry = 0;
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

void writeMessageRaspberry(char message[8]) {

  int i = 0;
  
  for (i = 0; message[i] != '\0'; i++)
    messageToRaspberry[i] = message[i];

  messageToRaspberry[i] = '\0';
  
  iSendToRaspberry = 1;
}
