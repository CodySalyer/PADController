// ThrustMotor.h

#ifndef _THRUSTMOTOR_h
#define _THRUSTMOTOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class ThrustMotor
{

 private:
	

 public:
	 ThrustMotor();

};

extern ThrustMotor thrustMotor;

#endif

