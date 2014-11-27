/*recordar que el pin al que enchufan la rueda
tiene que tener el simbolo ~ de PWM*/

const int pinRuedaDerecha = 3;
const int pinRuedaIzquierda = 5;

void setup()
{
	Serial.begin(9600);
	pinMode(pinRuedaIzquierda, OUTPUT);
	pinMode(pinRuedaDerecha, OUTPUT);
}

void loop()
{
	/*no olviden pasar como parametro de la funcion la velocidad entre 0 y 254*/
	adelante(180);
	Serial.println("corriendo.");
	delay(2000);
	detener();
	Serial.println("stop");
	delay(1000);
	girarDerecha(100);
	delay(500);
}

void adelante(int velocidad){
	analogWrite(pinRuedaDerecha, velocidad);
	analogWrite(pinRuedaIzquierda, velocidad);
}

void girarDerecha(int velocidad){
	analogWrite(pinRuedaIzquierda, velocidad);
	analogWrite(pinRuedaDerecha, 0);
}

void girarIzquierda(int velocidad){
	analogWrite(pinRuedaDerecha, velocidad);
	analogWrite(pinRuedaIzquierda, 0);
}

void detener(){
	analogWrite(pinRuedaDerecha, 0);
	analogWrite(pinRuedaIzquierda, 0);
}