
#include <SPI.h>
#include <Ethernet.h>

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


//***********SENSOR***********




void setup() {
  // Espera 1 segundo para que se inicie la tarjeta Ethernet
  delay(1000);
    // Inicializa la tarjeta ethernet mediante DHCP
  Ethernet.begin(mac);
   // Imprime la direccion IP de la tarjeta
  //Serial.print("Direccion IP: ");
 // Serial.println(Ethernet.localIP())
}

void loop() {
//*************SENSORES**********


//************SENSORES*********


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
