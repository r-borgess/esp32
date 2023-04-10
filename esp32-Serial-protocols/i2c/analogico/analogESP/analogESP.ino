#include <Wire.h>

const int SLAVE_ADDRESS = 8; 
const int POT_PIN = 36; //pino do potenciômetro

int potValue = 0;

void setup() {
  Serial.begin(115200);
  pinMode(POT_PIN, INPUT);
  Wire.begin(); // Inicia a comunicação I2C
}

void loop() {
  int potValue = analogRead(POT_PIN); // lê o valor do potenciômetro
   
  // Envia o valor mapeado para o dispositivo I2C conectado
  Wire.beginTransmission(SLAVE_ADDRESS); // endereço do dispositivo I2C
  Wire.write(potValue); // escreve o valor mapeado
  Wire.endTransmission();
}
