// SteeringMotor.h

#ifndef _STEERINGMOTOR_h
#define _STEERINGMOTOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class SteeringMotor
{

 protected:

 public:
	 byte enablePin;
	 byte directionPin;
	 byte brakePin;
	 byte potPin;

	 SteeringMotor(byte EnablePin, byte DirectionPin, byte BrakePin, byte PotPin);
};

extern SteeringMotor steeringMotor;

#endif

