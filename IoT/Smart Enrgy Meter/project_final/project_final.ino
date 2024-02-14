#define BLYNK_TEMPLATE_ID "TMPLXzXJWjie"
#define BLYNK_TEMPLATE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "ax-V2Mugt_TQuG6xacaDn2PSrT2ZHUhL"

#include <ZMPT101B.h>
#include "ACS712.h"
#include<WiFi.h>
#include<WiFiClient.h>
#include<BlynkSimpleEsp32.h>

#define SENSITIVITY 500.0f

BlynkTimer timer;

char ssid[] = "POCO M2 Pro";
char pass[] = "00000000";

ZMPT101B voltageSensor(26, 50.0);
ACS712  ACS(25, 3.3, 4095, 185);



void setup() {
Serial.begin(115200);

voltageSensor.setSensitivity(SENSITIVITY);

WiFi.begin(ssid, pass);
while(WiFi.status()!=WL_CONNECTED){
    delay(1000);
    Serial.println("NO....");
}

Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
float average = 0;
float voltage=0;

//Taking reading from ACS712
for (int i = 0; i < 100; i++){
   average += ACS.mA_AC();
}
float mA = average / 100.0; //final current

//Taking reading from ZMPT
voltage = voltageSensor.getRmsVoltage();
float power = voltage*mA;  //calculating power

//printing readings on Serial monitor
Serial.println("readingsssss.........");
Serial.println(mA/1000);
Serial.println(voltage);
Serial.println(power/1000);

//sending data to Blynk_2.0
Blynk.virtualWrite(V8, voltage);
Blynk.virtualWrite(V9, mA/1000); 
Blynk.virtualWrite(V10, power/1000);
  
delay(1000);
}
