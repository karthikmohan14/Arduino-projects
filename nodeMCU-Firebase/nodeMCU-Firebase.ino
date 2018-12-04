#include <ESP8266WiFi.h>
#include<FirebaseArduino.h>
#include <DHT.h>

#define FIREBASE_HOST "node-mcu-34585.firebaseio.com/" //Your Firebase Project URL goes here without "http:" , "\" and "/"
#define FIREBASE_AUTH "rFRVF3Nz2Hk4Yhe19QxtInutE0HJoMc1r44n0hsu" //Your Firebase Database Secret goes here

#define WIFI_SSID "kabilan" //your WiFi SSID for which yout NodeMCU connects
#define WIFI_PASSWORD "kabikabi123"//Password of your wifi network 

#define DHTTYPE DHT11
DHT dht(D5, DHTTYPE);
uint8_t temperature, humidity;

void setup() {

  Serial.begin(115200); //baud rate ,if you want to see the process in the serial monitor ,same baud rate should be set.
  WiFi.begin(WIFI_SSID,WIFI_PASSWORD);
  Serial.print("Connecting to WiFi - ");
  Serial.println(WIFI_SSID);
  while (WiFi.status()!=WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected:");
  Serial.println(WiFi.localIP());
  dht.begin();
  delay(500);
  Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
}
void firebasereconnect()
{
  Serial.println("Trying to reconnect");
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
    Serial.println();
  }
void loop() {
  if (Firebase.failed()) {
      Serial.print("Failed to connect");
      Serial.println(Firebase.error());
      Serial.println();
      Serial.println();
      firebasereconnect();
      return;
  }
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();
  delay(500);
  Serial.print("Temperature = ");
  Serial.print(temperature);
  Serial.print("  Humidity = ");
  Serial.println(humidity);
  
  Firebase.setString("temperature",String(temperature));
  Firebase.setString("humidity",String(humidity));
  
  Serial.println("Database updated");
  Serial.println();
  delay(2000);
}
