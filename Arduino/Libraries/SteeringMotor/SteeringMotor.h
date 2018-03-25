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

 private:
	 byte enablePin;
	 byte directionPin;
	 byte brakePin;
	 byte speedPin;
	 byte potPin;

 public:
	 
	 bool enabled;
	 bool brakeEngaged;
	 bool motorDirection;

	 SteeringMotor(byte EnablePin, byte DirectionPin, byte BrakePin, byte PotPin);

	 Enabled(bool enableMotor);
	 EngageBrake(bool brakeState);
	 SetSpeed(int speed);
};

extern SteeringMotor steeringMotor;

#endif

