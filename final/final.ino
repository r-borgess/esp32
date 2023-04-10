#define LED_BUTTON 13 //led digital
#define BUTTON 25 // botao (digital)
#define LED_POT 26 // led analogico
#define POT 36 // potenciometro (analogico)
#define LED_SERIAL 23

int buttonState = 0; //estado do botao
int potValue = 0; //valor do potenciometro

//parametros pwm
const int freq = 5000; // frequencia
const int ledChannel_A = 0; // canal de geração do sinal analogico
const int resolution_A = 12; // resolução de 12 bits

//parametros serial
const int ledChannel_S = 1; // canal de geração do sinal serial
const int resolution_S = 12; // resolução de 12 bits
const int freq_S = 5000; // frequencia do serial

void setup() {
  //analogico
  ledcSetup(ledChannel_A, freq, resolution_A);
  ledcAttachPin(LED_POT, ledChannel_A);
  pinMode(POT, INPUT);

  //digital
  pinMode(LED_BUTTON, OUTPUT);
  pinMode(BUTTON, INPUT);
  attachInterrupt(digitalPinToInterrupt(BUTTON), ligaLed, CHANGE);

  //serial
  ledcSetup(ledChannel_S, freq_S, resolution_S);
  ledcAttachPin(LED_SERIAL, ledChannel_S);
  Serial.begin(9600);
}

void loop() {
//analogico
  // lendo valor do potenciômetro
  potValue = analogRead(POT);
  // convertendo o valor lido para o intervalo 0-255
  ledcWrite(ledChannel_A, potValue);

//serial
  // verificando se há valores disponíveis na serial
  if (Serial.available() > 0) {
    // lendo valor enviado pela serial
    int val = Serial.parseInt();
    // verificando se o valor está dentro do intervalo válido (0-1024)
    if (val >= 0 && val <= 4096) {
      // enviando valor para o LED3
      ledcWrite(ledChannel_S, val);
    } else {
      // informando valor inválido
      Serial.println("Valor fora do intervalo permitido (0-1024)");
    }
  }
}

//funçao de interrupção para i/o digital
void ligaLed() {
   // lendo o estado do botão
  buttonState = digitalRead(BUTTON);
  // se o botão estiver pressionado, acionar o LED_BUTTON
  if (buttonState == HIGH) {
    digitalWrite(LED_BUTTON, HIGH);
  } else {
    digitalWrite(LED_BUTTON, LOW);
  }
}
