#define BLYNK_AUTH_TOKEN ""

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "";
char pass[] = "";

DHT dht; 
BlynkTimer timer;

void sendSensor()
{
  float h = dht.getHumidity();
  float t = dht.getTemperature();
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  
  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t);
}

void setup()
{
  
  Serial.begin(115200);

  Blynk.begin(auth, ssid, pass);
  
  dht.setup(12);//D6
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();
}
