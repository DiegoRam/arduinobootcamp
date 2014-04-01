#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

const int arduinoId = 10;
const int greenLed = 4;
const int pinTransmiter = 3;
int sensorState = 1 ;
void setup(){
	Serial.begin(9600);
	mySwitch.enableTransmit(pinTransmiter);
	pinMode(greenLed, OUTPUT);

}

void loop(){

	digitalWrite(greenLed, HIGH);        
	mySwitch.send(arduinoId + sensorState, 12);
	digitalWrite(greenLed, LOW);
        sensorState = sensorState * (-1);
    
	Serial.print("broadcast message..");
        Serial.println(arduinoId + sensorState);
	delay(2000);
	
}
