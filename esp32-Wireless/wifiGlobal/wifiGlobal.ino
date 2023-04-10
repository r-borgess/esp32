/*#define BLYNK_TEMPLATE_ID "<id>"
#define BLYNK_TEMPLATE_NAME "<name>"
#define BLYNK_AUTH_TOKEN "<token>"*/
#define BLYNK_PRINT Serial
#define POT 36
#define LED 2

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

/* 
char ssid[] = "<ssid>";
char pass[] = "<password>";
*/

BlynkTimer timer;

BLYNK_WRITE(V0)
{
  int pinValue=param.asInt();
  digitalWrite(LED,pinValue);
  }
void setup()
{
  Serial.begin(115200);
  pinMode(POT,INPUT);
  pinMode(LED,OUTPUT);
 
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
 
}
 
void loop()
{
  Blynk.run();
  int potvalue=analogRead(POT);
  Blynk.virtualWrite(V1,potvalue);
}
