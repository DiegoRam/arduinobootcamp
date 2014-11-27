/*
  Programa para seguidor de lineas programable versión Arduino 3.0
  Falta parte de la comunicación. Se usará una variable string para las órdenes recibidas
  Las órdenes serán:
  0=Detener
  1=Recto
  2=Doblar a la Derecha
  3=Doblar a la Izquierda
  Ésta versión 3.0 usará 4 sensores, serán 2 para seguir la linea y 2 para controlar la ejecución de las órdenes.
  Diferencia a 2.0: Sigue la linea por presencia, apaga el motor opuesto al sensor que la pierde.
 */

// the setup routine runs once when you press reset:
int velocidadDer100 = 170;
int velocidadIzq100 = 170;
int ruedaDer1 = 2;
int ruedaDer2 = 3;
int ruedaIzq1 = 4;
int ruedaIzq2 = 5;
int pwmDer = 9;
int pwmIzq = 10;
boolean lineaIzq = true;
boolean lineaDer = true;
boolean ordenIzq = true;
boolean ordenDer = true;
int sensibilidad = 100;
String ordenesRecibidas = String ("20");
int ordenActual = 0;
int miliSeg = 50;

void setup() {
  pinMode(ruedaDer1, OUTPUT);
  pinMode(ruedaDer2, OUTPUT);
  pinMode(ruedaIzq1, OUTPUT);
  pinMode(ruedaIzq2, OUTPUT); 
  //Serial.begin(9600);
}


// the loop routine runs over and over again forever:
/*void loop() {
  
  chequearSensores();  
  
  if (!ordenDer && !ordenIzq){
    siguienteOrden();
  }
  else {
    seguirLinea();
  }
  
} 
*/

void loop (){
girarDer();
delay (1000);
girarIzq();
delay (1000);

}

// Función que decide en base a la orden recibida
void siguienteOrden () {

  if ((ordenesRecibidas.charAt(ordenActual))== '1' ){
    ordenSeguir();
  }
  else {
    if ((ordenesRecibidas.charAt(ordenActual))== '2' ){
      ordenDoblarDer();
    }
    else {
      if ((ordenesRecibidas.charAt(ordenActual))== '3' ){
        ordenDoblarIzq();
      }
      else {
        detener();
        while(true);
      }
    }
  }  
}


void chequearSensores(){

  // Lectura de los tres sensores.
  int sensorValueLineaIzq = analogRead(A0);
  int sensorValueLineaDer = analogRead(A2);
  int sensorValueOrdenIzq = analogRead(A3);
  int sensorValueOrdenDer = analogRead(A4);
  //String SensorResults = String (sensorValueLineaIzq) + " " + String(sensorValueLineaDer) + " " + String(sensorValueOrdenIzq) + " " + String(sensorValueOrdenDer);
  //Serial.println(SensorResults);
  //  delay (100);  
  
  // Estableciendo variables booleanas según lectura de los sensores
  if (sensorValueLineaIzq < sensibilidad)
    lineaIzq = true;
  else
    lineaIzq = false;
  if (sensorValueLineaDer < sensibilidad)
    lineaDer = true;
  else
    lineaDer = false;
  if (sensorValueOrdenDer < sensibilidad)
    ordenDer = true;
  else
    ordenDer = false;
  if (sensorValueOrdenIzq < sensibilidad)
    ordenIzq = true;
  else
    ordenIzq = false;
  
}

void seguirLinea() {

  if (lineaIzq && lineaDer)
    detener();
     
  if (lineaIzq && !lineaDer)
    doblarDer();
     
  if (!lineaIzq && lineaDer)
    doblarIzq();
     
  if (!lineaIzq && !lineaDer)
    avanzarRecto();      
}

//Inicio rutinas de órdenes

void ordenSeguir(){
  while (!ordenDer && !ordenIzq ){
    chequearSensores();
    seguirLinea();
  }
  ordenActual++;
}

void ordenDoblarDer(){
  while (!ordenDer && !ordenIzq){
    chequearSensores();
    girarDer();
  }
  while (!(!ordenDer && !ordenIzq)){
    chequearSensores();
    girarDer();
  }
  ordenSeguir();
}

void ordenDoblarIzq(){
  while (!ordenDer && !ordenIzq){
    chequearSensores();
    girarIzq();
  }
  while (!(!ordenDer && !ordenIzq)){
    chequearSensores();
    girarIzq();
  }
  ordenSeguir();
}

// Fin rutinas de ordenes, entra por siguienteOrden() y sale siempre por ordenSeguir().

   
// Inicio de rutinas de los tipos de movimientos.

void avanzarRecto() {
//  detener();
//  delay (miliSeg);
  analogWrite(pwmDer, velocidadDer100);
  analogWrite(pwmIzq, velocidadIzq100);
  digitalWrite(ruedaDer1,HIGH);
  digitalWrite(ruedaDer2,LOW);
  digitalWrite(ruedaIzq1,HIGH);
  digitalWrite(ruedaIzq2,LOW);
//  delay (miliSeg);
}

void doblarDer() {
//  detener();
//  delay (miliSeg);
  analogWrite(pwmDer, 0);
  analogWrite(pwmIzq, velocidadIzq100);
  digitalWrite(ruedaDer1,HIGH);
  digitalWrite(ruedaDer2,LOW);
  digitalWrite(ruedaIzq1,HIGH);
  digitalWrite(ruedaIzq2,LOW);
//  delay (miliSeg);
}

void doblarIzq() {
//  detener();
//  delay (miliSeg);
  analogWrite(pwmDer, velocidadDer100);
  analogWrite(pwmIzq, 0);
  digitalWrite(ruedaDer1,HIGH);
  digitalWrite(ruedaDer2,LOW);
  digitalWrite(ruedaIzq1,HIGH);
  digitalWrite(ruedaIzq2,LOW);
//  delay (miliSeg);
}


void detener() {
  digitalWrite(ruedaDer1,LOW);
  digitalWrite(ruedaDer2,HIGH);
  digitalWrite(ruedaIzq1,LOW);
  digitalWrite(ruedaIzq2,HIGH);
  delay (200);                                                                                                          
  analogWrite(pwmDer, 0);
  analogWrite(pwmIzq, 0);
  digitalWrite(ruedaDer1,LOW);
  digitalWrite(ruedaDer2,LOW);
  digitalWrite(ruedaIzq1,LOW);
  digitalWrite(ruedaIzq2,LOW);
  
}

void girarDer(){
  detener();
  delay(miliSeg);
  analogWrite(pwmDer, velocidadDer100);
  analogWrite(pwmIzq, velocidadIzq100);
  digitalWrite(ruedaDer1,HIGH);
  digitalWrite(ruedaDer2,LOW);
  digitalWrite(ruedaIzq1,LOW);
  digitalWrite(ruedaIzq2,HIGH);
  delay(miliSeg);
}

void girarIzq(){
  detener();
  delay(miliSeg);
  analogWrite(pwmDer, velocidadDer100);
  analogWrite(pwmIzq, velocidadIzq100);
  digitalWrite(ruedaDer1,LOW);
  digitalWrite(ruedaDer2,HIGH);
  digitalWrite(ruedaIzq1,HIGH);
  digitalWrite(ruedaIzq2,LOW);
  delay(miliSeg);
}

// Fin de las rutinas de los tipos de movimientos.

