#include "CommunicationSerial.h"

void setup() {
  Serial2.begin(9600);
  Serial.begin(115200);
}

void loop() {
  updateSerial();

  char message[8];
  message[0] = '\0';

  getMessage(message);

  if (message[0] != '\0') {
    Serial.println(message);
  }
}
