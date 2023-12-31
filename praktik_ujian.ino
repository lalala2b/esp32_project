#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL6EfdxUIEo"
#define BLYNK_TEMPLATE_NAME "Dwiky"
#define BLYNK_AUTH_TOKEN "nEsBPCaDk8tQzKUv1vG075vINvZ_xH0a"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

char ssid[] = "lalala";
char pass[] = "00000000";

// Variable pin

#define pinDHT 18
#define typeDHT DHT11

#define relay0 12 // lampu 1
#define relay1 14 // lampu 2
#define relay2 27 // lampu 3
#define relay3 26 // kipas

#define switch0 25 // lampu 1
#define switch1 33 // lampu 2
#define switch2 32 // lampu 3

DHT dht(pinDHT,typeDHT);
LiquidCrystal_I2C lcd(0x27,20,4);

// Virtual pin
#define virtual0 V0
#define virtual1 V1
#define virtual2 V2
#define virtual3 V3
#define virtual4 V4

// state var
int state0,state1,state2,state3;

BLYNK_CONNECTED(){
  Blynk.syncVirtual(virtual0);
  Blynk.syncVirtual(virtual1);
  Blynk.syncVirtual(virtual2);
  Blynk.syncVirtual(virtual3);
  Blynk.syncVirtual(virtual4);
}
BLYNK_WRITE(virtual0){
  int tempstate=param.asInt();
  digitalWrite(relay0,tempstate);
}
BLYNK_WRITE(virtual1){
  int tempstate=param.asInt();
  digitalWrite(relay1,tempstate);
}
BLYNK_WRITE(virtual2){
  int tempstate=param.asInt();
  digitalWrite(relay2,tempstate);
}
BLYNK_WRITE(virtual3){
  int tempstate=param.asInt();
  digitalWrite(relay3,tempstate);
}

void setup(){
  Serial.begin(9600);
  dht.begin();
  lcd.init();
  lcd.backlight();

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  pinMode(relay0,OUTPUT);
  pinMode(relay1,OUTPUT);
  pinMode(relay2,OUTPUT);
  pinMode(relay3,OUTPUT);

  pinMode(switch0,INPUT_PULLUP);
  pinMode(switch1,INPUT_PULLUP);
  pinMode(switch2,INPUT_PULLUP);
}

void loop(){
  if(state0 != digitalRead(switch0)){ 
    state0 = !state0;
    digitalWrite(relay0,state0);
    Blynk.virtualWrite(virtual0,state0);
    Serial.println("success");
    delay(200);
  }
  if(state1 != digitalRead(switch1)){ 
    state1 = !state1;
    digitalWrite(relay1,state1);
    Blynk.virtualWrite(virtual1,state1);
    Serial.println("success");
    delay(200);
  }
  if(state2 != digitalRead(switch2)){ 
    state2 = !state2;
    digitalWrite(relay2,state2);
    Blynk.virtualWrite(virtual2,state2);
    Serial.println("success");
    delay(200);
  }
  Blynk.run();
  
  float temp=dht.readTemperature();
  float hum=dht.readHumidity();

  lcd.setCursor(0,0);
  lcd.print("Temp: "+String(temp)+"C");
  lcd.setCursor(0,1);
  lcd.print("Hum : "+String(hum)+"%");
  Blynk.virtualWrite(virtual4,temp);
  delay(200);
  lcd.clear();
}
