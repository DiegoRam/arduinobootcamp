
void setup(){
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
 digitalWrite(3, LOW);
 digitalWrite(4, LOW);
 digitalWrite(5, LOW);
 digitalWrite(6, LOW);
  
}

void loop(){
 digitalWrite(3, HIGH);
 digitalWrite(4, LOW);
 digitalWrite(5, LOW);
 digitalWrite(6, LOW);
 delay(1);
 
  digitalWrite(3, LOW);
 digitalWrite(4, HIGH);
 digitalWrite(5, LOW);
 digitalWrite(6, LOW);

delay(500);
 digitalWrite(3, LOW);
 digitalWrite(4, LOW);
 digitalWrite(5, HIGH);
 digitalWrite(6, LOW);
 delay(500);
  digitalWrite(3, LOW);
 digitalWrite(4, LOW);
 digitalWrite(5, LOW);
 digitalWrite(6, HIGH);
delay(500);

 
}

