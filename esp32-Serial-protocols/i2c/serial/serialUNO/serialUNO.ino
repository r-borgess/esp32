#include <Wire.h>
#define LED_SERIAL 6

const int SLAVE_ADDRESS = 8;

void setup() {
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receiveData);
  pinMode(LED_SERIAL, OUTPUT);
  analogWrite(LED_SERIAL, 0);
  Serial.begin(9600);
}

void loop() {
}

void receiveData(int byteCount) {
  int data = Wire.read();
  analogWrite(LED_SERIAL, data);
  Serial.print(data);
}
