# Praactica 8
## Análisis del código
```c
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
```

Este código establece una comunicación entre dos puertos seriales. Los datos recibidos en Serial se envían a Serial2, y cualquier respuesta recibida en Serial2 se imprime en Serial.

1. Configuración inicial con la función Setup
   - Se inicializan los dos puertos series a 115200 baudios.
2. Bucle principal con la función Loop
   - Comprueba si hay datos disponibles en `Serial`.
   - Lee el byte recibido.
   - Envía el byte leído a través de `Serial2`.
   - Lectura de respuesta en `Serial2`.
     - Comprueba si hay datos disponibles en `Serial2`.
     - Lee el byte recibido de `Serial2`.
     - Imprime el byte recibido en `Serial`.