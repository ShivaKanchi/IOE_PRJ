const int trigPin = D0; 
const int echoPin = D1; 
const int LED1 = D2;
const int LED2 = D3;
const int LED3 = D4;
const int BUZZER = D5;
long duration;
int distance;

void setup() {
pinMode(LED1 , OUTPUT);
pinMode(LED2 , OUTPUT);
pinMode(LED3 , OUTPUT);
pinMode(BUZZER , OUTPUT);
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
Serial.begin(9600); // Starts the serial communication
}

void loop() {  
digitalWrite(LED1, LOW);
digitalWrite(LED2, LOW);
digitalWrite(LED3, LOW);
// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculating the distance
distance= duration*0.034/2;
// Prints the distance on the Serial Monitor

if (distance >= 75) {
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(BUZZER, LOW);
    Serial.print("4 Distance: ");
    Serial.println(distance);
    delay(1000);

  }
  if (distance >= 0 && distance <= 5) {
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
    digitalWrite(BUZZER, HIGH);
    delay(1000);
    Serial.print("1 Distance: ");
    Serial.println(distance);
  }
  if (distance > 5 && distance <=35) {
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    delay(1000);
    digitalWrite(LED3, LOW);
    digitalWrite(BUZZER, LOW);
    Serial.print("2 Distance: ");
    Serial.println(distance);
  }
  if (distance > 35 && distance <=75 ) {
    digitalWrite(LED1, HIGH);
    delay(1000);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(BUZZER, LOW);
    Serial.print("3 Distance: ");
    Serial.println(distance);
  }
}
