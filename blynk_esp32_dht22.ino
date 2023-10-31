#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID "TMPL6qOAvs_zX"
#define BLYNK_TEMPLATE_NAME "DHT22"
#define BLYNK_AUTH_TOKEN "3DjhpntJHUdu9BkwJ8BrzaeG0XR3Gi6H"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include "DHTesp.h"

const int DHT_PIN = 4;
DHTesp dht;

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "lalala";
char pass[] = "00000000";

BlynkTimer timer;

void sendSensor(){
  TempAndHumidity data = dht.getTempAndHumidity();
  Serial.println("Temp: "+String(data.temperature, 2)+"°C");
  Serial.println("Humidity: "+String(data.humidity, 1)+"%");
  Serial.println("...");
  Blynk.virtualWrite(V0, data.temperature);
  Blynk.virtualWrite(V1, data.humidity);
}

void setup(){
  Serial.begin(9600);
  Blynk.begin(auth,ssid,pass);
  //pinMode(LED, OUTPUT);
  dht.setup(DHT_PIN,DHTesp::DHT22);
  timer.setInterval(1000L, sendSensor);
}

void loop(){
  Blynk.run();
  timer.run();
}