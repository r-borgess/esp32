#include <Wire.h>

const int SLAVE_ADDRESS = 8;
const int LED_BUT = 6;

void setup() {
  Wire.begin(SLAVE_ADDRESS); // Endereço do escravo
  Wire.onReceive(receiveData);
  pinMode(LED_BUT, OUTPUT);
  Serial.begin(9600);
}

void loop() {
}

void receiveData(int byteCount) {
    while (Wire.available()) {
      int brilho = Wire.read(); 
      map(brilho, 0, 4095, 0, 255);
      analogWrite(LED_BUT, brilho);
    }
}
