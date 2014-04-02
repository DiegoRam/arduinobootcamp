//Constants

#include <RCSwitch.h>

const int pinTrigger = 4;
const int pinEcho = 3; // The echo pin must to have PWM support
const int nosePin = 5;
const int pinChannel1 = 7;
const int takeTime = 5;
const int timeUnit = 1000;
const int pintTransmitter = 9;
const int redLed = 6;
int sensorState = 0;

const int arduinoId = 20;


boolean state = false;

//Threshold to activate in cms
const int perimeter = 90;

RCSwitch mySwitch = RCSwitch();

long microsecondsToCm(long microseconds){
  return microseconds / 29 / 2 ;
}

void turnOn()
{
	digitalWrite(nosePin, HIGH);
	digitalWrite(pinChannel1, LOW);
}

void turnOff()
{
	digitalWrite(nosePin, LOW);
	digitalWrite(pinChannel1, HIGH);
}

void sendStatus(){
	Serial.print("sending sensor status: ");
	Serial.println(sensorState);
	mySwitch.send(arduinoId + sensorState ,12);
        //mySwitch.sendTriState("from 2");
	digitalWrite(redLed, HIGH);

}

void setup()
{
	Serial.begin(9600);
	pinMode(pinTrigger, OUTPUT);
	pinMode(nosePin, OUTPUT);
	pinMode(pinChannel1, OUTPUT);
    pinMode(redLed, OUTPUT);
    digitalWrite(nosePin, LOW);
    digitalWrite(pinChannel1, HIGH);

    mySwitch.enableTransmit(pintTransmitter);
}

void loop()
{
	long duration , cm;
	digitalWrite(redLed, LOW);

  	pinMode(pinTrigger, OUTPUT);
  	digitalWrite(pinTrigger, LOW);
  	delayMicroseconds(2);
  	digitalWrite(pinTrigger,HIGH);
  	delayMicroseconds(10);
  	digitalWrite(pinTrigger, LOW);

	pinMode(pinEcho, INPUT);
  	duration = pulseIn(pinEcho, HIGH);
  	cm = microsecondsToCm(duration);

  	Serial.println(cm);

  	//Desicion
        
  	if(cm >= perimeter)
  	{
  	  Serial.print("turning off at ");
      Serial.print(takeTime);
      Serial.println(" seconds");
  		turnOff();
  		sensorState = 0 ; 
  	} else {
  		Serial.println("turning on...");
  		turnOn();
  		sensorState = 1 ;
  	}
  	sendStatus();
    delay(timeUnit);
}
