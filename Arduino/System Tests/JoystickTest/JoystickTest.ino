#include <Joystick.h>

/////////////////////////////////NOTES/////////////////////////////////////
/*
Yellow wire plugged into A0
Green wire plugged into A1");
*/
///////////////////////////////END NOTES///////////////////////////////////

Joystick whiteJoystick(A0, A1);

void setup()
{
	Serial.begin(9600);
	Serial.println("White Joystick Test");
	Serial.println("Yellow plugged into A0");
	Serial.println("Green plugged into A1");

	whiteJoystick.xMin = 225;
	whiteJoystick.xMax = 791;
	whiteJoystick.yMin = 230;
	whiteJoystick.yMax = 797;
}

void loop()
{	
	Serial.print("Y axis: ");
	Serial.print(whiteJoystick.getY());
	Serial.print(" X axis: ");
	Serial.print(whiteJoystick.getX());
	Serial.print(" Magnitude: ");
	Serial.println(whiteJoystick.getMagnitude());

	delay(250);
}
