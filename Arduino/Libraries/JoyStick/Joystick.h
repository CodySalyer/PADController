// Joystick.h

#ifndef _JOYSTICK_h
#define _JOYSTICK_h

#include "Arduino.h"

class Joystick
{
 private:

	 byte xPosition = 0;
	 byte yPosition = 0;
	 byte theta = 0;
	 byte magnitude = 0;

	 byte xAxisPin;
	 byte yAxisPin;
	 byte thetaPin;
	 byte buttonPin;

 public:

	float xMax = 0;
	float xMin = 0;
	float yMax = 0;
	float yMin = 0;
	float thetaMax = 0;
	float thetaMin = 0;

	// Constructor for 2Dof joystick
	Joystick(byte XAxisPin, byte YAxisPin);

	// Constructor for 2 Dof + 1 button Joystick
	Joystick(byte XAxisPin, byte YAxisPin, byte ButtonPin);

	// Constructor for 3 Dof + 1 button Joystick
	Joystick(byte XAxisPin, byte YAxisPin, byte ThetaPin, byte ButtonPin);

	// Returns the normalized x value from the joystick [-100,100]
	int getX();

	// Returns the normalized y value from the joystick [-100,100]
	int getY();

	// Returns the angle from the y axis from the joystick [-90,90]
	int getTheta();

	// Returns the magnitude of the vector from the joystick [0,100]
	int getMagnitude();

	// Returns the state of the button on the joystick
	bool getButton();
};

//extern Joystick joystick;

#endif

