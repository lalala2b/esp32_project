// BLYNK setup
#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL6Mr7ZOakC"
#define BLYNK_TEMPLATE_NAME "Dwiky"
#define BLYNK_AUTH_TOKEN "d19uAbayezWbwJ5eB2IP7kXTrdQaukjr"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// ssid dan password
char ssid[] = "lalala";
char pass[] = "00000000";

#define pinDHT 18
#define typeDHT DHT11

DHT dht(pinDHT,typeDHT);
LiquidCrystal_I2C lcd(0x27,20,4);

// pin esp32
#define relay0 12 // lampu
#define relay1 14 // lampu
#define relay2 27 // lampu
#define relay3 26 // kipas

#define switch0 25
#define switch1 33
#define switch2 32

// pin virtual
#define virtual0 V0 // lampu 1
#define virtual1 V1 // lampu 2
#define virtual2 V2 // lampu 3
#define virtual3 V3 // kipas
#define virtual4 V4 // suhu

// state variable
int state0,state1,state2,state3;

BLYNK_CONNECTED(){
  Blynk.syncVirtual(virtual0);
  Blynk.syncVirtual(virtual1);
  Blynk.syncVirtual(virtual2);
  Blynk.syncVirtual(virtual3);
}

BLYNK_WRITE(virtual0){
  int tempstate = param.asInt();
  digitalWrite(relay0,!digitalRead(relay0));
  Serial.println("success");
}
BLYNK_WRITE(virtual1){
  int tempstate = param.asInt();
  digitalWrite(relay1,!digitalRead(relay1));
  Serial.println("success");
}
BLYNK_WRITE(virtual2){
  int tempstate = param.asInt();
  digitalWrite(relay2,!digitalRead(relay2));
  Serial.println("success");
}
BLYNK_WRITE(virtual3){
  int tempstate = param.asInt();
  digitalWrite(relay3,tempstate);
  Serial.println("success");
}

void setup(){
  Serial.begin(9600);
  dht.begin();
  lcd.init();
  lcd.backlight();
  Blynk.begin(BLYNK_AUTH_TOKEN,ssid,pass);

  pinMode(relay0,OUTPUT);
  pinMode(relay1,OUTPUT);
  pinMode(relay2,OUTPUT);
  pinMode(relay3,OUTPUT);

  pinMode(switch0,INPUT_PULLUP);
  pinMode(switch1,INPUT_PULLUP);
  pinMode(switch2,INPUT_PULLUP);
}

void loop(){
  Blynk.run();

  if (state0!=digitalRead(switch0)){
    state0=!state0;
    digitalWrite(relay0,!digitalRead(relay0));
    Blynk.virtualWrite(virtual0,digitalRead(relay0));
  }else if (state1!=digitalRead(switch1)){
    state1=!state1;
    digitalWrite(relay1,!digitalRead(relay1));
    Blynk.virtualWrite(virtual1,digitalRead(relay1));
  }else if (state2!=digitalRead(switch2)){
    state2=!state2;
    digitalWrite(relay2,!digitalRead(relay2));
    Blynk.virtualWrite(virtual2,digitalRead(relay2));
  }
  
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Suhu  : "+String(temp)+"C");
  lcd.setCursor(0,1);
  lcd.print("Humid : "+String(hum)+"%");

  Blynk.virtualWrite(virtual4,temp);
  delay(200);
}
