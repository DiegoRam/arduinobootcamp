//Constants
const int pinTrigger = 4;
const int pinEcho = 3; // The echo pin must to have PWM support
const int nosePin = 5;
const int pinChannel1 = 7;
const int takeTime = 5;
const int timeUnit = 1000;

boolean state = false;

//Threshold to activate in cms
const int perimeter = 90;

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

void setup()
{
	Serial.begin(9600);
	pinMode(pinTrigger, OUTPUT);
	pinMode(nosePin, OUTPUT);
	pinMode(pinChannel1, OUTPUT);
        digitalWrite(nosePin, LOW);
        digitalWrite(pinChannel1, HIGH);
}

void loop()
{
	long duration , cm;
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
  	} else {
  		Serial.println("turning on...");
  		turnOn();
  	}
    delay(timeUnit);
}
