#include <Arduino.h>

void setup() {
  Serial.begin(115200); // Inicializa la comunicación serial a 9600 baudios
  Serial2.begin(115200);
}

void loop() {
  while (Serial.available() > 0) { // Comprueba si hay datos disponibles para leer
    char receivedChar = Serial.read(); // Lee el byte recibido
    delay(10);
    Serial2.write(receivedChar);
    delay(10);
    while (Serial2.available() > 0)
    {
    char recivedChar1 = Serial2.read();
    delay(10);
    Serial.print("Datos recibidos: ");
    Serial.println(recivedChar1); // Imprime el byte recibido
    delay(10);
    }
  }
}
