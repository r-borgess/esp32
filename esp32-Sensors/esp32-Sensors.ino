/*#define BLYNK_TEMPLATE_ID "<id>"
#define BLYNK_TEMPLATE_NAME "<name>"
#define BLYNK_AUTH_TOKEN "<token>"
*/

#define YL69 34

#define LDR 35

#define MHRD_D 33
#define MHRD_A 32
#define RELAY 22

#define BLYNK_PRINT Serial
#include <WiFi.h>
//#include <ESP8266WiFi.h> 
#include <BlynkSimpleEsp32.h>
#include <math.h>

#include <DHT.h>


char auth[] = BLYNK_AUTH_TOKEN;
/*
char ssid[] = "<ssid>";  // type your wifi name
char pass[] = "<oassword>";  // type your wifi password
*/
bool relayState = LOW;
int pinValue = 0;

BlynkTimer timer;


#define DHTPIN 14 //Connect Out pin to D2 in NODE MCU
#define DHTTYPE DHT11  
DHT dht(DHTPIN, DHTTYPE);

BLYNK_WRITE(V6){
  pinValue=param.asInt();
  if(pinValue == 1){
   digitalWrite(RELAY, !relayState);
   Serial.println("Solenoide LIGADA!"); 
  }else{
    Serial.println("Solenoide DESLIGADA!"); 
  }
  Serial.println(pinValue);
 }

void sendRain()
{
  int mhrd = analogRead(MHRD_A); // Read the analog value from the sensor
  double rainValue = pow((mhrd / 4096), 2.5) * 25.4;
  
  // Send the rain intensity value to the Blynk server
  if (digitalRead(MHRD_D)){
    Serial.println("CHUVA");
   }else{
    Serial.println("SEM CHUVA");
   }
  Blynk.virtualWrite(V4, rainValue);
  Blynk.virtualWrite(V5, digitalRead(MHRD_D));
  Serial.print("Chuva: ");
  Serial.println(rainValue);
}

void sendLDR(){
  int lumi = analogRead(LDR);
  lumi = map(lumi, 4095, 0, 0, 100);
  Blynk.virtualWrite(V3,  lumi);

  Serial.print("Luminosidade: ");
  Serial.println(lumi);
}

void sendSoilMoisture()
{
  int soilMoisture = analogRead(YL69);

  // Convert the analog value to a percentage between 0-100%
  soilMoisture = map(soilMoisture, 4095, 0, 0, 100);

  // Send the soil moisture value to the Blynk server
  Blynk.virtualWrite(V2, soilMoisture);

  Serial.print("Umidade do Solo: ");
  Serial.print(soilMoisture);
  Serial.println("%");
}

void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
    Blynk.virtualWrite(V0, t);
    Blynk.virtualWrite(V1, h);
    Serial.print("Temperature : ");
    Serial.print(t);
    Serial.print("    Humidity : ");
    Serial.println(h);
}
void setup()
{
  Serial.begin(115200);
  pinMode(RELAY, OUTPUT);
  Blynk.begin(auth, ssid, pass);
  dht.begin();
  // Set intervals for calling the sendSensor() and sendSoilMoisture() functions
  timer.setInterval(5000L, sendSensor);
  timer.setInterval(5001L, sendSoilMoisture);
  timer.setInterval(5002L, sendLDR);
  timer.setInterval(5003L, sendRain);
}

void loop()
{
  Blynk.run();

  timer.run();
 }
