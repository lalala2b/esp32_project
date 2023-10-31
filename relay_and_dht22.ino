#include "DHT.h"

#define DHTPIN 4 //Pin DHT
#define KIPAS 13 //Pin Kipas
#define DHTTYPE DHT22 //Jenis DHT yang digunakan

DHT dht(DHTPIN,DHTTYPE);

void setup(){
  Serial.begin(9600);
  pinMode(KIPAS,OUTPUT);
  
  dht.begin();
}

void loop(){
  delay(1000);
  digitalWrite(12,HIGH);

  float t = dht.readTemperature();

  if (isnan(t)){
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Untuk menampilkan data temperature
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println("°C");

  // memeriksa kondisi suhu, jika diatas 28 °C maka kipas menyala
  if(t>28){
    digitalWrite(KIPAS,LOW);
    Serial.println("Kipas Menyala");
  }else{
    digitalWrite(KIPAS,HIGH);
    Serial.println("Kipas Mati");
  }
}