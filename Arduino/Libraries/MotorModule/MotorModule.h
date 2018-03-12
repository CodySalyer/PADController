// Motor.h

#ifndef _MOTOR_h
#define _MOTOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class MotorModule
{

 protected:

 public:
	 byte enablePin;
	 byte directionPin;
	 byte brakePin;
	 byte potPin;

	 MotorModule(byte EnablePin, byte DirectionPin, byte BrakePin, byte PotPin);
};

extern MotorModule Motor;

#endif

