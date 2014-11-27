#include <Wire.h>
#define SLAVE_ADDRESS 0x04

int calibrationTime = 15;
long unsigned int lowIn;
long unsigned int pause = 1500;

boolean lockLow = true;
boolean takeLowTime;

int pirPin = 12;
int pinChannel1 = 7;
int greenLedPin = 5;
int protocolControlPin = 13; 
int redLedPin = 6;
int micPin = A0;
int micValue = 0;
int number = 0;
int state = 0;
int movementState = 0;
String dummie = "Hola Narigon";



void setup(){
  Serial.begin(9600);
  pinMode(pirPin, INPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(pinChannel1, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(protocolControlPin, OUTPUT);
  digitalWrite(pirPin, LOW);

  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receiveData);
  Wire.onRequest(sendSensorStatus);

  Serial.println("Calibrating sensor ");
  for(int i=0; i<calibrationTime; i++){
  	Serial.print(".");
  	delay(1000);
  }
  Serial.println("done");
  Serial.println("Sensor active");
  delay(50);
}

void loop(){
  micValue = getMicValue();
  delay(500);

	if(digitalRead(pirPin) == HIGH){
		digitalWrite(greenLedPin, HIGH);
		//digitalWrite(pinChannel1, LOW);
		if(lockLow){
			lockLow = false;
			Serial.println("----");
			Serial.print("motion detected at ");
			Serial.println(millis()/1000);
			Serial.println(" secs.");
			delay(50);	
		}
		takeLowTime = true;
	}
	if(digitalRead(pirPin) == LOW){
		digitalWrite(greenLedPin, LOW);
		//digitalWrite(pinChannel1, HIGH);
		if(takeLowTime){
			lowIn = millis();
			takeLowTime = false;
		}
		if(!lockLow && millis() - lowIn > pause){
			lockLow = true;
			Serial.print("Motion ended at");
			Serial.print(millis() - pause / 1000);
			Serial.println(" sec.");
			delay(50);
		}
	}
}


void sendSensorStatus(){
  Serial.println("sending data..");
  String response = "{movement: " + String(movementState) + "}";
  Wire.write("{movement: true}");
}

void receiveData(int byteCount){
  Serial.println("recieving data..");
  while(Wire.available()){
    number = Wire.read();
    if(number == 1){
      if(state == 0){
        digitalWrite(protocolControlPin, HIGH);
        state = 1;
      } else {
        digitalWrite(protocolControlPin, LOW);
        state = 0;
      }
    }
  }
}

int getMicValue(){
  int tmp = analogRead(micPin);
  Serial.print("sound Levels: ");
  Serial.println(micValue);
  if(micValue> 512) {
    digitalWrite(redLedPin, HIGH);
  } else {
    digitalWrite(redLedPin, LOW);
  }
  return (tmp);
}

