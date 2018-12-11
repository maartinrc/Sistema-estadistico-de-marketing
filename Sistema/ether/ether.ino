
#include <SPI.h>
#include <Ethernet.h>

#include <Time.h>
#include <TimeLib.h>


#include <DHT.h>
// Definimos el pin digital donde se conecta el sensor
#define DHTPIN 13
// Dependiendo del tipo de sensor
#define DHTTYPE DHT11

byte mac[] = {0x00,0xAA,0xBB,0xCC,0xDE, 0x02};

IPAddress ip(192,168,1,99);

// Inicializa la instancia client
EthernetClient client;

// Direccion del servidor
char server[] = "localhost";

// Variable de tiempo de la ultima conexion en milisegundos
unsigned long ultimaConexion = 0; 
         
// Estado de la ultima conexion
boolean ultimoEstado = false;

// Intervalo en milisegundos entre conexiones
const unsigned long intervaloConexion = 60000;// 1 minuto


//***********SENSOR***********
const int EchoPin = 5;
const int TriggerPin = 6;
float distancia;
long tiempo;
boolean bandera = false;

//***********SENSOR***********
int conta = 0; //Variable para guardar el conteo de los pulsos
int sensor = 8;


//***************SENSOR************************
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Espera 1 segundo para que se inicie la tarjeta Ethernet
  delay(1000);
    // Inicializa la tarjeta ethernet mediante DHCP
  Ethernet.begin(mac);
   // Imprime la direccion IP de la tarjeta
  //Serial.print("Direccion IP: ");
 // Serial.println(Ethernet.localIP())

   pinMode(TriggerPin, OUTPUT);
   pinMode(EchoPin, INPUT);
 time_t t = now();//Declaramos la variable time_t t 
 setTime(0,0,0,1,01,2018);

 pinMode(sensor, INPUT);

 dht.begin();
 
}

void loop() {
//*************SENSORES**********
  digitalWrite(TriggerPin, HIGH);  //se envía un pulso para activar el sensor
  delayMicroseconds(10);
  digitalWrite(TriggerPin, LOW);

  tiempo = (pulseIn(EchoPin, HIGH)/2);

  distancia = float(tiempo * 0.0343);

  if (distancia >= 15) {
   setTime(0,0,0,1,01,2018);                     }
else if(distancia <= 7){
 
 time_t t = now();//Declaramos la variable time_t t
 Serial.print(minute(t));
 Serial.print(": ");   
 Serial.println(second(t)); 

 delay(1000);
} 

//************SENSORES*********
if ( digitalRead(sensor) == LOW ) { 
      conta++; //Incrementa el contador 
      Serial.println(conta);
      delay(400);
      }


/*********Sensores***********/


   // Esperamos 5 segundos entre medidas
  delay(5000);
 
  // Leemos la humedad relativa
  float h = dht.readHumidity();
  // Leemos la temperatura en grados centígrados (por defecto)
  float t = dht.readTemperature();
  // Leemos la temperatura en grados Fahreheit
  float f = dht.readTemperature(true);
 
  // Comprobamos si ha habido algún error en la lectura
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Error obteniendo los datos del sensor DHT11");
    return;
  }
 Serial.print("Humedad: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
  Serial.println();


//**********************

  // Si hay datos que llegan por la conexion los envia a la puerta serial
  if (client.available()) {
    char c = client.read();
    Serial.print(c);
  }

  // Si no hay conexion de red y se conecto correctamente la ultima vez
  // detiene el cliente Ehternet
  if (!client.connected() && ultimoEstado) {
    Serial.println();
    Serial.println("Desconectando...");
    client.stop();
  }

  // Si no esta conectado y han pasado X segundos (intervaloConexion) 
  // despues de la ultima conexion envia datos al servidor
  if(!client.connected() && (millis() - ultimaConexion > intervaloConexion)) {
    httpRequest();
  }
  // Actualiza la variable ultimoEstado 
  ultimoEstado = client.connected();

}

// Realiza la conexion http al servidor
void httpRequest() {
  // Se conecta al servidor en el puerto 80 (web)
  if (client.connect(server, 80)) {
    // Envia el requerimiento al servidor via GET
    client.print("GET /registraDatos.php?mac");
    client.print(mac);
    client.print("&tiempo=");
    client.print(tiempo);
    client.print("&conteoPersonas=");
    client.print(conteo);
    client.print("&humedad=");
    client.print(humedad);
    client.print("&temperatura=");
    client.print(temp);
    client.println(" HTTP/1.1"); //checar 
    client.print("Host:");
    client.println(server);
   // client.println("User-Agent: Arduino-Ethernet"); // hasta aqui
    client.println("Connection: close");
    client.println();

    // Actualiza el tiempo en milisegundos de la ultima conexion
    ultimaConexion = millis();
  } 
  else {
    // Si la conexion fallo se desconecta
   Serial.println("Error al conectarse al servidor");
   Serial.println("Desconectando...");
    client.stop();
  }
}
