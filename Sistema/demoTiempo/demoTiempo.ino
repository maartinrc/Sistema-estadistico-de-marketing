#include <Time.h>
#include <TimeLib.h>

const int EchoPin = 5;
const int TriggerPin = 6;
float distancia;
long tiempo;
boolean bandera = false;
 
void setup() {
   Serial.begin(9600);
   pinMode(TriggerPin, OUTPUT);
   pinMode(EchoPin, INPUT);
 time_t t = now();//Declaramos la variable time_t t     
// Serial.println("segundos****** "+second(t)); 
     setTime(0,0,0,1,01,2018);
}
 
void loop() {

  digitalWrite(TriggerPin, HIGH);  //se envía un pulso para activar el sensor
  delayMicroseconds(10);
  digitalWrite(TriggerPin, LOW);

  // medimos el pulso de respuesta
  tiempo = (pulseIn(EchoPin, HIGH)/2);
 
  // dividido por 2 por que es el
  // tiempo que el sonido tarda
  // en ir y en volver
  // ahora calcularemos la distancia en cm
  // sabiendo que el espacio es igual a la velocidad por el tiempo
  // y que la velocidad del sonido es de 343m/s y que el tiempo lo
  // tenemos en millonesimas de segundo
 
  distancia = float(tiempo * 0.0343);

  // Serial.print("Distancia: "); // imprime la distancia en el Monitor Serie
  // Serial.println(distancia);
   

if (distancia >= 15) {
   setTime(0,0,0,1,01,2018);                     }
else if(distancia <= 7){
 
 time_t t = now();//Declaramos la variable time_t t
 Serial.print(minute(t));
 Serial.print(": ");   
 Serial.println(second(t)); 
} 


delay(1000);
}
