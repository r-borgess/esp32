// Código do Arduino UNO

#include <Wire.h>

const int SLAVE_ADDRESS = 8;
const int LED_BUT = 13;

void setup() {
  Wire.begin(SLAVE_ADDRESS); // Endereço do escravo
  Wire.onReceive(receiveEvent);
  pinMode(LED_BUT, OUTPUT);
  Serial.begin(9600);
}

void loop() {
}

void receiveEvent(int howMany) {
  int state = Wire.read();
  if (state == HIGH) {
  digitalWrite(LED_BUT, HIGH);
} else {
  digitalWrite(LED_BUT, LOW);
}

}
