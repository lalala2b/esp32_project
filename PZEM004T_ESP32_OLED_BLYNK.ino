#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID "TMPL6YRwn4sJ7"
#define BLYNK_TEMPLATE_NAME "PZEM 004T"
#define BLYNK_AUTH_TOKEN "pB8m7DtE-XxNVT4LJxLxYkGJ9UcKY3jl"

#include <PZEM004Tv30.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// BLYNK INIT
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "lalala";
char pass[] = "00000000";

BlynkTimer timer;

// OLED INIT || ESP32 PIN SDA 21, SCL 22
#define DISPLAY_WIDTH     128
#define DISPLAY_HEIGHT    64

Adafruit_SSD1306 display(DISPLAY_WIDTH, DISPLAY_HEIGHT, &Wire, -1);

// PCB INIT || PZEM TX 16, RX 17
#if !defined(PZEM_RX_PIN) && !defined(PZEM_TX_PIN)
#define PZEM_RX_PIN 16
#define PZEM_TX_PIN 17
#endif

#if !defined(PZEM_SERIAL)
#define PZEM_SERIAL Serial2
#endif

#if defined(ESP32)
PZEM004Tv30 pzem(PZEM_SERIAL, PZEM_RX_PIN, PZEM_TX_PIN);
#elif defined(ESP8266)

#else
PZEM004Tv30 pzem(PZEM_SERIAL);
#endif
// END OF PCB INIT

void setup() {
    // Debugging Serial port
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Address 0x3D for 128x64
    Serial.begin(115200);
    // Uncomment in order to reset the internal energy counter
    // pzem.resetEnergy()
    Blynk.begin(auth,ssid,pass);
    timer.setInterval(1000L, sendData);
}

void loop() {
    // Print the custom address of the PZEM
    Blynk.run();
    timer.run();

    display.setCursor(0, 0);
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);

    Serial.print("Custom Address:");
    Serial.println(pzem.readAddress(), HEX);
    display.println("Custom Address: "+String(pzem.readAddress(),HEX));

    // Read the data from the sensor
    float voltage = pzem.voltage();
    float current = pzem.current();
    float power = pzem.power();
    float energy = pzem.energy();
    float frequency = pzem.frequency();
    float pf = pzem.pf();

    // Check if the data is valid
    if(isnan(voltage)){
        Serial.println("Error reading voltage");
        display.println("Error reading voltage");
    } else if (isnan(current)) {
        Serial.println("Error reading current");
        display.println("Error reading current");
    } else if (isnan(power)) {
        Serial.println("Error reading power");
        display.println("Error reading power");
    } else if (isnan(energy)) {
        Serial.println("Error reading energy");
        display.println("Error reading energy");
    } else if (isnan(frequency)) {
        Serial.println("Error reading frequency");
        display.println("Error reading frequency");
    } else if (isnan(pf)) {
        Serial.println("Error reading power factor");
        display.println("Error reading power factor");
    } else {

        // Print the values to the Serial console
        Serial.print("Voltage: ");      Serial.print(voltage);      Serial.println("V");
        Serial.print("Current: ");      Serial.print(current);      Serial.println("A");
        Serial.print("Power: ");        Serial.print(power);        Serial.println("W");
        Serial.print("Energy: ");       Serial.print(energy,3);     Serial.println("kWh");
        Serial.print("Frequency: ");    Serial.print(frequency, 1); Serial.println("Hz");
        Serial.print("PF: ");           Serial.println(pf);

        //DISPLAY OLED
        display.println("Voltage: "+String(voltage)+"V");
        display.println("Current: "+String(current)+"A");
        display.println("Power: "+String(power)+"W");
        display.println("Energy: "+String(energy, 3)+"kWh");
        display.println("Frequency: "+String(frequency, 1)+"Hz");
        display.println("PF: "+String(pf));
        
    }

    display.display();
    Serial.println();
    delay(2000);
}

// Display BLYNK
void sendData(){
  Blynk.virtualWrite(V0,pzem.voltage());
  Blynk.virtualWrite(V1,pzem.current());
  Blynk.virtualWrite(V2,pzem.power());
  Blynk.virtualWrite(V3,pzem.energy());
  //Blynk.virtualWrite(V4,pzem.frequency());
  Blynk.virtualWrite(V4,pzem.pf());
}