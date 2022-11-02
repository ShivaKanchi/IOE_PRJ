#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

#define WLAN_SSID       "ShivaKanchi"
#define WLAN_PASS       "02020202"
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME  "shivakanchi"
#define AIO_KEY       "aio_qqoT44CorsiLXy3lxCdZ3TiYCNsf"

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
Adafruit_MQTT_Publish WaterLevel = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/WaterLevel_TOD");
Adafruit_MQTT_Publish MotorButton = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/Motor_TOD");

//pins
const int trigPin = D0; 
const int echoPin = D1; 
const int LED1 = D5;//green
const int LED2 = D6;//yellow
const int LED3 = D7;//red
const int BUZZER = D2;
const int MOTOR = D4;//relay,motor
int motorst=0;
long duration;
int distance;

void setup() {
  
pinMode(LED1 , OUTPUT);
pinMode(LED2 , OUTPUT);
pinMode(LED3 , OUTPUT);
pinMode(BUZZER , OUTPUT);
pinMode(MOTOR , OUTPUT);
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
 
  MQTT_Connect();
}

void loop() {
  
//calculating water distance from sensor
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
distance= duration*0.034/2;

WaterLevel.publish(distance);
MotorButton.publish(motorst);
delay(1500);


//contitions

  if (distance >= 0 && distance <= 9) {
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
    digitalWrite(BUZZER, HIGH);
    digitalWrite(MOTOR,LOW);
    motorst=0;
    delay(1000);
    Serial.print("1 Distance: ");
    Serial.println(distance);
  }
  else if (distance >= 10 && distance <= 49) {
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(MOTOR,HIGH);
    delay(1000);
    motorst=0;
    digitalWrite(LED3, LOW);
    digitalWrite(BUZZER, LOW);
    Serial.print("2 Distance: ");
    Serial.println(distance);
    
    }
  else if (distance >= 50 && distance <=75 ) {
    digitalWrite(LED1, HIGH);
    digitalWrite(MOTOR,HIGH);
    delay(1000);
    motorst=1;
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(BUZZER, LOW);
    Serial.print("3 Distance: ");
    Serial.println(distance);
  }
   else if (distance >= 76) {
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(BUZZER, LOW);
    digitalWrite(MOTOR,LOW);
    Serial.print("4 Distance: ");
    Serial.println(distance);
    motorst=0;
    delay(1000);
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
