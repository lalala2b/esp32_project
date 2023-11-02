#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TEMPLATE ID"
#define BLYNK_TEMPLATE_NAME "TEMPLATE NAME"
#define BLYNK_AUTH_TOKEN "TOKEN"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

BlynkTimer timer;

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "";
char pass[] = "";

#define relay0 13
#define relay1 12
#define relay2 14
#define relay3 27

#define sw0 17
#define sw1 18
#define sw2 19
#define sw3 21

int rState0 = 0;
int rState1 = 0;
int rState2 = 0;
int rState3 = 0;

#define vpin0 V0
#define vpin1 V1
#define vpin2 V2
#define vpin3 V3

BLYNK_CONNECTED(){
  Blynk.syncVirtual(vpin0);
  Blynk.syncVirtual(vpin1);
  Blynk.syncVirtual(vpin2);
  Blynk.syncVirtual(vpin3);
}

BLYNK_WRITE(vpin0){
  rState0 = param.asInt();
  digitalWrite(relay0, rState0);
}
BLYNK_WRITE(vpin1){
  rState1 = param.asInt();
  digitalWrite(relay1, rState1);
}
BLYNK_WRITE(vpin2){
  rState2 = param.asInt();
  digitalWrite(relay2, rState2);
}
BLYNK_WRITE(vpin3){
  rState3 = param.asInt();
  digitalWrite(relay3, rState3);
}

void setup() {
  Blynk.begin(auth,ssid,pass);

  pinMode(sw0,INPUT_PULLUP);
  pinMode(sw1,INPUT_PULLUP);
  pinMode(sw2,INPUT_PULLUP);
  pinMode(sw3,INPUT_PULLUP);

  pinMode(relay0,OUTPUT);
  pinMode(relay1,OUTPUT);
  pinMode(relay2,OUTPUT);
  pinMode(relay3,OUTPUT);
}

void loop() {
  Blynk.run();
  timer.run();

  push_button();
}

void push_button(){
  delay(20);
  if(digitalRead(sw0)==LOW){
    control_relay(0);
    Blynk.virtualWrite(vpin0,rState0);
  }else if(digitalRead(sw1)==LOW){
    control_relay(1);
    Blynk.virtualWrite(vpin1,rState1);
  }else if(digitalRead(sw2)==LOW){
    control_relay(2);
    Blynk.virtualWrite(vpin2,rState2);
  }else if(digitalRead(sw3)==LOW){
    control_relay(3);
    Blynk.virtualWrite(vpin3,rState3);
  }
}

void control_relay(int relay){
  if(relay==0){
    rState0 = !rState0;
    digitalWrite(relay0,rState0);
  }else if(relay==1){
    rState1 = !rState1;
    digitalWrite(relay1,rState1);
  }else if(relay==2){
    rState2 = !rState2;
    digitalWrite(relay2,rState2);
  }else if(relay==3){
    rState3 = !rState3;
    digitalWrite(relay3,rState3);
  }
  delay(50);
}
