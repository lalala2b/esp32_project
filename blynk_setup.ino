#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID "TMPL6ruODf8Sa"
#define BLYNK_TEMPLATE_NAME "Basic LED"
#define BLYNK_AUTH_TOKEN "IVzVnhZhEbtD6zdgUvP2Cqn2_2Wg9TMD"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

int pinLED = 12;
int pinLED2 = 13;

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "lalala";
char pass[] = "00000000";

BLYNK_WRITE(V0){
   int pinValue = param.asInt();
   digitalWrite(pinLED, pinValue);
}

BLYNK_WRITE(V1){
   int pinValue = param.asInt();
   digitalWrite(pinLED2, pinValue);
}

void setup(){
  Serial.begin(115200);
  Blynk.begin(auth,ssid,pass);
  pinMode(pinLED, OUTPUT);
  pinMode(pinLED2, OUTPUT);
}

void loop(){
  Blynk.run();
}