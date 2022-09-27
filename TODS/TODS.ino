#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

#define WLAN_SSID       "ShivaKanchi"
#define WLAN_PASS       "02020202"

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME  "shivakanchi"
#define AIO_KEY       "aio_mdjV48TSm7M5utr7SVZpGGuJnX64" 

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
Adafruit_MQTT_Publish WaterLevel = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/WaterLevel_TOD");
Adafruit_MQTT_Publish motor = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/Buzzer_TOD");

//pins
const int trigPin = D0; 
const int echoPin = D1; 
const int LED1 = D2;
const int LED2 = D3;
const int LED3 = D4;
const int BUZZER = D5;
const int MOTOR = D6;
int motorst=0;
long duration;
int distance;

 
void setup() {
pinMode(LED1 , OUTPUT);
pinMode(LED2 , OUTPUT);
pinMode(LED3 , OUTPUT);
pinMode(BUZZER , OUTPUT);
pinMode(trigPin, OUTPUT); 
pinMode(echoPin, INPUT); 
Serial.begin(9600);

Serial.println("Connecting to WiFi...");
  WiFi.begin(WLAN_SSID,WLAN_PASS);
  while(WiFi.status()!= WL_CONNECTED){
    Serial.print(".");
    delay(500);
    }
  Serial.println("WiFi Connected !");
}


void loop() {  
  
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
distance= duration*0.034/2;

MQTT_Connect();
if (!WaterLevel.publish(distance))
  {
    Serial.println("Failed");
  }
  else
  {
    Serial.println("OK!");
  }
  
  if (!motor.publish(motorst))
  {
    Serial.println("Failed");
  }
  else
  {
    Serial.println("OK!");
  }
  delay(3000);

if (distance >= 75) {
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(BUZZER, LOW);
    Serial.print("4 Distance: ");
    Serial.println(distance);
    delay(500);

  }
  if (distance >= 0 && distance <= 5) {
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
    digitalWrite(BUZZER, HIGH);
    motorst=1;
    delay(500);
    Serial.print("1 Distance: ");
    Serial.println(distance);
    
  }
  if (distance > 5 && distance <=35) {
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    motorst=1;
    delay(500);
    digitalWrite(LED3, LOW);
    digitalWrite(BUZZER, LOW);
    Serial.print("2 Distance: ");
    Serial.println(distance);
  }
  if (distance > 35 && distance <=75 ) {
    digitalWrite(LED1, HIGH);
    motorst=0;
    delay(500);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(BUZZER, LOW);
    Serial.print("3 Distance: ");
    Serial.println(distance);
  }
}

void MQTT_Connect(){
     if(mqtt.connected()){
          return;
       }
     Serial.println("Connecting to MQTT...");
     int retries = 3,status;
     while((status = mqtt.connect()) != 0){
          Serial.println(mqtt.connectErrorString(status));
          Serial.println("Retrying after 5 secs....");
          delay(5000);
          retries--;
          if(retries == 0){
              while(1);   // reset the nodemcu
            }
      }
      Serial.println("MQTT Connected");
  }
