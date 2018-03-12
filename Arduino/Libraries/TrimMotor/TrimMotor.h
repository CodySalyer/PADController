// TrimMotor.h

#ifndef _TRIMMOTOR_h
#define _TRIMMOTOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class TrimMotor
{

 protected:

 public:
	 byte trimUpPin;
	 byte trimDownPin;
	 byte enablePin;
	

	 SteeringMotor(byte TrimUpPin, byte TrimDownPin, byte Enable);
};

extern TrimMotor trimMotor;

#endif

