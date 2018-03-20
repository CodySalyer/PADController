/*
Functions for Joystick library, contains 2 Dof, 2Dof with button & 3Dof with button
*/

#include "Joystick.h"

Joystick::Joystick(byte XAxisPin, byte YAxisPin, byte ThetaPin, byte ButtonPin)
{
	pinMode(ButtonPin, INPUT);
	pinMode(XAxisPin, INPUT);
	pinMode(YAxisPin, INPUT);
	pinMode(ThetaPin, INPUT);

	buttonPin = ButtonPin;
	xAxisPin = XAxisPin;
	yAxisPin = YAxisPin;
	thetaPin = ThetaPin;
}

Joystick::Joystick(byte XAxisPin, byte YAxisPin, byte ButtonPin)
{
	pinMode(XAxisPin, INPUT);
	pinMode(YAxisPin, INPUT);
	pinMode(ButtonPin, INPUT);

	xAxisPin = XAxisPin;
	yAxisPin = YAxisPin;
	buttonPin = ButtonPin;
	thetaPin = 0;
}

Joystick::Joystick(byte XAxisPin, byte YAxisPin)
{
	pinMode(XAxisPin, INPUT);
	pinMode(YAxisPin, INPUT);

	xAxisPin = XAxisPin;
	yAxisPin = YAxisPin;
	thetaPin = 0;
}

Joystick::getX() // linear interpolation to normalize value from [-100, 100]
{
	float xVolt = analogRead(xAxisPin);
	return(int)((-100) + (xVolt - xMin)*(200) / (xMax - xMin));
}

Joystick::getY() // linear interpolation to normalize value from [-100, 100]
{
	float yVolt = analogRead(yAxisPin);
	return(int)((-100) + (yVolt - yMin)*(200) / (yMax - yMin));
}

Joystick::getTheta() // linear interpolation to normalize value from [-90, 90]
{
	int tVolt = analogRead(thetaPin);
	return(-90 + (tVolt - thetaMin)*(90 - (-90)) / (thetaMax - thetaMin));
}

Joystick::getMagnitude() // linear interpolation to normalize value from [-100, 100]
{
	int magnitude = sqrt(pow(getX(), 2) + pow(getY(), 2));
	if (magnitude > 100) return 100;
	else return magnitude;
}

bool Joystick::getButton()
{
	bool state = digitalRead(buttonPin);
	return state;
}