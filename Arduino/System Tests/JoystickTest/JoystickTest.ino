#include "Motor.h"
void setup()
{
	Serial.begin(9600);
	Serial.println("Joystick Test");
	pinMode(A0, INPUT);
	pinMode(A1, INPUT);

}

void loop()
{	
	Serial.print("Y axis: ");
	Serial.print(analogRead(A0));
	Serial.print(" X axis: ");
	Serial.println(analogRead(A1));  
	delay(100);
}
