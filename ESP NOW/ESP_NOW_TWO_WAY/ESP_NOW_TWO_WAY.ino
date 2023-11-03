// BOX PUTIH

#include <esp_now.h>
#include <WiFi.h>
#include <DHTesp.h>
#include <Wire.h>
#include <LiquidCrystal.h>


// lcd tanpa I2C
LiquidCrystal lcd(2,4,15,5,18,19);
#define DHT_PIN 23
DHTesp dht;

float temperature;
float humidity;

float incomingTemp;
float incomingHum;

String success;
// gunakan address esp32 tujuan
uint8_t broadcastAddress[] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};

typedef struct struct_message{
  float temp;
  float hum;
}struct_message;

struct_message DHTread;

struct_message incomingMessage;

esp_now_peer_info_t peerInfo;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status){
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
  if(status==0){
    success = "Delivery Success :)";
  }else{
    success = "Delivery Fail :(";
  }
}

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData,int len){
  memcpy(&incomingMessage, incomingData, sizeof(incomingMessage));
  Serial.println("Bytes received: "+String(len));
  incomingTemp = incomingMessage.temp;
  incomingHum = incomingMessage.hum;
}

void setup(){
  Serial.begin(115200);
  lcd.begin(20,4);
  WiFi.mode(WIFI_STA);
  dht.setup(DHT_PIN,DHTesp::DHT11);
  
  if(esp_now_init() != ESP_OK){
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_send_cb(OnDataSent);

  memcpy(peerInfo.peer_addr,broadcastAddress,6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }

  esp_now_register_recv_cb(OnDataRecv);
}

void loop(){
  getReading();

  DHTread.temp = temperature;
  DHTread.hum = humidity;

  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &DHTread, sizeof(DHTread));

  if (result == ESP_OK){
    Serial.println("Sent with success");
  }else{
    Serial.println("Error sending the data");
  }
  updateDisplay();
  delay(1000);
}

void getReading(){
  TempAndHumidity data = dht.getTempAndHumidity();

  temperature = data.temperature;
  humidity = data.humidity;
}

void updateDisplay(){
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("Data Diterima");
  lcd.setCursor(0,2);
  lcd.print("Temp: "+String(incomingTemp)+"C");
  lcd.setCursor(0,3);
  lcd.print("Hum: "+String(incomingHum)+"%");

// Menampilkan di serial monitor
  Serial.println("Temp: "+String(incomingTemp)+"C");
  Serial.println("Hum: "+String(incomingHum)+"%");
}