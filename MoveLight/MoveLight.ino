int calibrationTime = 30;
long unsigned int lowIn;
long unsigned int pause = 5000;

boolean lockLow = true;
boolean takeLowTime;

int pirPin = 2;
int pinChannel1 = 7;
int greenLedPin = 5;

void setup(){
  Serial.begin(9600);
  pinMode(pirPin, INPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(pinChannel1, OUTPUT);
  digitalWrite(pirPin, LOW);
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
	if(digitalRead(pirPin) == HIGH){
		digitalWrite(greenLedPin, HIGH);
		digitalWrite(pinChannel1, LOW);
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
		digitalWrite(pinChannel1, HIGH);
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
