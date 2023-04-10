#define LED 23
#define SERIAL 9600

int buttonState = 0;
int potValue = 0;

const int freq = 5000;
const int ledChannel = 0;
const int resolution = 12;

void setup() {
  ledcSetup(ledChannel, freq, resolution);
  ledcAttachPin(LED, ledChannel);
  Serial.begin(SERIAL);
}

void loop() {
  if(Serial.available() > 0){
    int val = Serial.parseInt();
    if(val >= 0 && val <= 4096){
      ledcWrite(ledChannel, val);
    }else{
      Serial.println("Valor fora do intervalo permitido (0-4096)");
    }
  }
}
