//**********ULTRASONICO*******************
#include <Time.h>
const int EchoPin = 5;
const int TriggerPin = 6;
float distancia;
long tiempo;
boolean bandera = false;
String mins, secs;
////////////***********ULTRASONICO**********
int conta = 0; //Variable para guardar el conteo de los pulsos
int sensor = 8;

void setup() {
pinMode(TriggerPin, OUTPUT);
   pinMode(EchoPin, INPUT);
 time_t t = now();//Declaramos la variable time_t t     
// Serial.println("segundos****** "+second(t)); 
     setTime(0,0,0,1,01,2018);
  
  Serial.begin(9600);
  pinMode(sensor, INPUT);
  }

void loop() { 
//***********ULTRASONICO***********
  digitalWrite(TriggerPin, HIGH);  //se envía un pulso para activar el sensor
  delayMicroseconds(10);
  digitalWrite(TriggerPin, LOW);

  // medimos el pulso de respuesta
  tiempo = (pulseIn(EchoPin, HIGH)/2);
  
  distancia = float(tiempo * 0.0343);

  if (distancia >= 15) {
   setTime(0,0,0,1,01,2018);                     }
else if(distancia <= 7){
 
 time_t t = now();//Declaramos la variable time_t t
 mins = minute(t);
 secs = second(t);
 Serial.print(mins);
 Serial.print(": ");   
 Serial.println(secs); 
} 


//delay(1000);
  //*****************ULTRASONICO*************
  if ( digitalRead(sensor) == LOW ) { 
      conta++; //Incrementa el contador
      Serial.print("Contador"); 
      Serial.println(conta);
      delay(400);
      } 
    }
