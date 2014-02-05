#include <AFMotor.h>

AF_DCMotor motorLeft(2, MOTOR12_64KHZ);
AF_DCMotor motorRight(1, MOTOR12_64KHZ);


const int trigPin = 9;
const int echoPin = 10;
const int limitCerca = 10;
const int limiteLejos = 25;
const int limiteStopLejos = 55;

void setup(){
  Serial.begin(9600);
  motorLeft.setSpeed(100);
  motorRight.setSpeed(100); 
}

void loop(){
  long duration , cm;
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  cm = microsecondsToCm(duration);
  
  //Desicion
  
  if(cm > limiteLejos && cm <= limiteStopLejos){
    motorLeft.run(FORWARD);
    motorRight.run(FORWARD);
    Serial.print("ADELANTE");
    Serial.println();

  } else {
    if(cm <= limitCerca){
      motorLeft.run(BACKWARD);
      motorRight.run(BACKWARD);
      Serial.print("ATRAS");
      Serial.println();

    } else {
     motorLeft.run(RELEASE);
     motorRight.run(RELEASE);
     Serial.print("STOP");
     Serial.println();
   } 
  }
  
  delay(100);
  
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  
  delay(100);
}

long microsecondsToCm(long microseconds){
  return microseconds / 29 / 2 ;
}

