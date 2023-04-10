#include <Wire.h>

const int nChars = 32;
char string[nChars];
String valor;
char fim = '\n';
char c;
int val = 0;
int i = 0;

void setup() {
  Serial.begin(115200);
  Wire.begin();
}

void loop() {
  while(Serial.available() > 0){
    c = Serial.read();
    if(c != fim){
      string[i] = c;
      i++;
      if(i >= nChars){
        i = nChars - 1;
      }
    }else{
      string[i] = '\0';
      i = 0;
    }
  }
  valor = String(string);
  val = valor.toInt();
  if(val >= 0 && val <= 255){
    Wire.beginTransmission(8);
    Wire.write(val);
    Wire.endTransmission(); 
   }else{
    Serial.println("Valor fora do intervalo permitido: 0 - 255");
    Wire.beginTransmission(8);
    Wire.write(0);
    Wire.endTransmission(); 
   }
}
