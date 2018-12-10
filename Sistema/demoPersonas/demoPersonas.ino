int conta = 0; //Variable para guardar el conteo de los pulsos
int sensor = 8;

void setup() {
  Serial.begin(9600);
  pinMode(sensor, INPUT);
  }

void loop() { 
  if ( digitalRead(sensor) == LOW ) { 
      conta++; //Incrementa el contador 
      Serial.println(conta);
      delay(400);
      } 
    }
