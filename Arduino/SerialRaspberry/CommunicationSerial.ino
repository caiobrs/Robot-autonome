
char message[8];
int indexMessage;
bool messageFinished = false;

void updateSerial() {
  if (Serial2.available()) {
    char caracter = Serial2.read();
    
    if (caracter == '#') {
      indexMessage = -1;
      messageFinished = false;
    }
    else if (caracter == '@') {
      message[indexMessage] = '\0';
      messageFinished = true;
    }
    else 
      message[indexMessage] = caracter;

    if (indexMessage == 8)
      indexMessage = 0;
    else 
      indexMessage++;
  }
}

void getMessage(char messageEmpty[8]) {
  if (messageFinished == true) {
    messageFinished = false;
    int index = 0;

    while (message[index] != '\0') {
      messageEmpty[index] = message[index];
      index++;
    }

    messageEmpty[index] = '\0';
    message[0] = '\0';
  }
  else {
    messageEmpty[0] = '\0';
  }
}
