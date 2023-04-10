#include <Wire.h>

const int SLAVE_ADDRESS = 8; 
const int BUT_PIN = 25; //pino do botão
int potValue = 0;

void setup() {
  Serial.begin(115200);
  pinMode(BUT_PIN, INPUT);
  Wire.begin(); // Inicia a comunicação I2C
}

void loop() {
  Wire.beginTransmission(SLAVE_ADDRESS);
  Wire.write(digitalRead(BUT_PIN));
  Wire.endTransmission();
  
  delay(100); // adiciona um pequeno delay
}
