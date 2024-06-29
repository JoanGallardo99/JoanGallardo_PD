#include <Arduino.h>
#include "BluetoothSerial.h"

int Pin1 = 15; //P
int Pin2 = 2; //N
int Pin3 = 4; //P
int Pin4 = 0; //N

int Speed = 255;

BluetoothSerial SerialBT;
char t;

void setup() 
{
    pinMode(Pin1, OUTPUT);
    pinMode(Pin2, OUTPUT);
	pinMode(Pin3, OUTPUT);
    pinMode(Pin4, OUTPUT);
    Serial.begin(115200);
    SerialBT.begin("ESP32RubenJoan");
    delay(500);
    Serial.println("ESP32 en busqueda");

    ledcSetup(0, 5000, 8); //Canal, frecuencia y resolución de 8 bits
	ledcSetup(1, 5000, 8);
	ledcSetup(2, 5000, 8);
	ledcSetup(3, 5000, 8);

	ledcAttachPin(Pin1, 0);
	ledcAttachPin(Pin2, 1);
	ledcAttachPin(Pin3, 2);
	ledcAttachPin(Pin4, 3);
}

void loop() 
{
    if(SerialBT.available())
    {
      t = SerialBT.read();
      Serial.println(t);

	
		if (t == '1')
		{
			Speed=165;
		}
		else if (t == '2')
		{
			Speed=195;
		}
		else if (t == '3')
		{
			Speed=225;
		}
		else if (t == '4')
		{
			Speed=255;
		}
    

		if(t == 'F')
		{
			
			ledcWrite(0, 0);
			ledcWrite(1, 200); 
			ledcWrite(2, 0);
			ledcWrite(3, 200); 
			Serial.println("Front"); //Front
			//digitalWrite(ledPin2, HIGH);
		}

		else if (t == 'P')
		{
			ledcWrite(1, 0);
			ledcWrite(0, 0); 
			ledcWrite(2, 0);
			ledcWrite(3, 0);
			Serial.println("Stop"); //Stop
			//digitalWrite(ledPin2, LOW);
		}

		else if (t == 'E')
		{
			
			ledcWrite(1, 210); 
			ledcWrite(2, 0);
			ledcWrite(3, 135);
			Serial.println("Forward Right"); //STOP
			//digitalWrite(ledPin2, LOW);
		}

		else if (t == 'Q')
		{
			ledcWrite(0, 0);
			ledcWrite(1, 135); 
			ledcWrite(2, 0);
			ledcWrite(3, 210);
			Serial.println("Forward Left"); //STOP
			//digitalWrite(ledPin2, LOW);
		}

		else if (t == 'R')
		{
			ledcWrite(0, 0);
			ledcWrite(1, 200); 
			ledcWrite(2, 200);
			ledcWrite(3, 0);
			Serial.println("Right"); //STOP
			//digitalWrite(ledPin2, LOW);
		}

		else if (t == 'L')
		{
			ledcWrite(0, 200);
			ledcWrite(1, 0); 
			ledcWrite(2, 0);
			ledcWrite(3, 200);
			Serial.println("Left"); 
			//digitalWrite(ledPin2, LOW);
		}

		else if (t == 'B')
		{
			ledcWrite(0, 200); //Back
			ledcWrite(1, 0);
			ledcWrite(2, 200);
			ledcWrite(3, 0);
			Serial.println("Backward"); 
		}

		else if (t == 'A')
		{
			ledcWrite(0, 135); //Back
			ledcWrite(1, 0);
			ledcWrite(2, 210);
			ledcWrite(3, 0);
			Serial.println("Backward Left"); 
		}

		else if (t == 'D')
		{
			ledcWrite(0, 210); //Back
			ledcWrite(1, 0);
			ledcWrite(2, 135);
			ledcWrite(3, 0);
			Serial.println("Backward Right"); 
		}
		
		delay(100);
	}
}



/*char t;
 
void setup() {
pinMode(13,OUTPUT);   //left motors  forward
pinMode(12,OUTPUT);   //left motors reverse
pinMode(11,OUTPUT);   //right  motors forward
pinMode(10,OUTPUT);   //right motors reverse
pinMode(9,OUTPUT);   //Led
Serial.begin(9600);
 
}
 
void loop() {
if(Serial.available()){
  t = Serial.read();
  Serial.println(t);
}
 
if(t == 'F'){            //move  forward(all motors rotate in forward direction)
  digitalWrite(13,HIGH);
  digitalWrite(11,HIGH);
}
 
else if(t == 'B'){      //move reverse (all  motors rotate in reverse direction)
  digitalWrite(12,HIGH);
  digitalWrite(10,HIGH);
}
  
else if(t == 'L'){      //turn right (left side motors rotate in forward direction,  right side motors doesn't rotate)
  digitalWrite(11,HIGH);
}
 
else  if(t == 'R'){      //turn left (right side motors rotate in forward direction, left  side motors doesn't rotate)
  digitalWrite(13,HIGH);
}

else if(t ==  'W'){    //turn led on or off)
  digitalWrite(9,HIGH);
}
else if(t == 'w'){
  digitalWrite(9,LOW);
}
 
else if(t == 'S'){      //STOP (all motors stop)
  digitalWrite(13,LOW);
  digitalWrite(12,LOW);
  digitalWrite(11,LOW);
  digitalWrite(10,LOW);
}
delay(100);
}*/

