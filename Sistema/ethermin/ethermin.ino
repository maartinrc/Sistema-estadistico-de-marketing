#include <Ethernet.h>
#include <SPI.h>
bool bandera;
#define trigger 2//pin que recibe la señal de la entrada
//****LIBRERIAS PARA CONTAR SEGUNDOS (PARA SENSOR ULTRASONICO)********
#include <Time.h>
//******LIBRERIAS PARA EL SENSOR DE TEMPERARUTA**********
#include <DHT.h>
//***********DECLRACION DE VARIABLES PARA EL DHT11*********
// Definimos el pin digital donde se conecta el sensor
#define DHTPIN 9
// Dependiendo del tipo de sensor
#define DHTTYPE DHT11

//***********DECLARACION DE VARIABLES PARA ETHERNET SHIELD W5100************
// Configuracion del Ethernet Shield
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFF, 0xEE}; // Direccion MAC
byte ip[] = { 192,168,1,100 }; // Direccion IP del Arduino
byte server[] = { 192,168,1,64 }; // Direccion IP del servidor
EthernetClient client;
String macos;

//**********DECLARACION DE VARAIBLES PARA SENSOR ULTRASONICO***************

const int EchoPin = 5;
const int TriggerPin = 6;
float distancia;
long tiempo;
int contTiempo;

//*****************  Inicializamos el sensor DHT11*****************
 DHT dht(DHTPIN, DHTTYPE);
 float humedad;
 float temperatura;

void setup(void) {
 attachInterrupt(digitalPinToInterrupt(trigger), interrupcion, RISING); //Se crea una interrupcion con el pin

  bandera = true;

   Serial.begin(9600);


  //****************INICIALIZAR ETHERNET SHIELD***********
  Ethernet.begin(mac,ip); // Inicializamos el Ethernet Shield
  delay(1000); // Esperamos 1 segundo de cortesia

  for(int i = 0; i<6; i++){
    macos+=String(mac[i]);

  }

  //***********INICIALIZACION DE VARIABLES DEL SENSOR ULTRASONICO************
  pinMode(TriggerPin, OUTPUT);
  pinMode(EchoPin, INPUT);
  time_t t = now();//Declaramos la variable time_t t
  setTime(0,0,0,1,01,2018);
  contTiempo = 0;

  //******************INICIALIZACION DE VARIABLES DE SENSOR DHT11**********

  // Comenzamos el sensor DHT
  dht.begin();

}

void loop(void) {
  while(bandera){

  //*************CONTEO DE SEGUNDOS (SENSOR ULTRASONICO)********************
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

if (distancia >= 15) {
   setTime(0,0,0,1,01,2018);                     }
else if(distancia <= 7){

 time_t t = now();//Declaramos la variable time_t t
 //Serial.print(minute(t));
 //Serial.print(": ");
 //Serial.println(second(t));
 if(second(t)!= 0){
  contTiempo += 1;
 }
}
//***************VERIFICACION DE TEMPERATURA Y HUMEDAD*************************
 // Leemos la humedad relativa
  humedad = dht.readHumidity();
  // Leemos la temperatura en grados centígrados (por defecto)
  temperatura = dht.readTemperature();
  // Leemos la temperatura en grados Fahreheit
 // float f = dht.readTemperature(true);

   // Comprobamos si ha habido algún error en la lectura
  /*if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Error obteniendo los datos del sensor DHT11");
    return;*/

      if (isnan(humedad) || isnan(temperatura)) {
    Serial.println("Error obteniendo los datos del sensor DHT11");
    return;
  }
/*
 Serial.print("Humedad: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
  Serial.println();
*/
   }
 //*************** HTTP REQUEST PARA ENVIAR DATOS VIA GET A ARCHIVO PHP*************************

  // Proceso de envio de muestras al servidor
Serial.println("Connecting...");
  if (client.connect(server, 80)>0) {  // Conexion con el servidor
    client.print("GET /SistemaEstadistico/PHP/insercionDatosMin.php?mac="); // Enviamos los datos por GET
    client.print(macos);
    client.print("&tiempo=");
    client.print(tiempo);
    client.print("&humedad=");
    client.print(humedad);
    client.print("&temperatura=");
    client.print(temperatura);
    client.println(" HTTP/1.0");
    client.println("User-Agent: Arduino 1.0");
    client.println();
    Serial.println("Conectado");
  } else {
    Serial.println("Fallo en la conexion");
  }
  if (!client.connected()) {
    Serial.println("Disconnected!");
  }
  client.stop();
  client.flush();
  delay(6000); // Espero un minuto antes de tomar otra muestra

}

void interrupcion() {
  bandera = !bandera;//Si se irrumpe la puerta, hay un cambio de estado de cerrado a abierto y viceversa
}
