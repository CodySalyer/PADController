// TrimMotor.h

#ifndef _TRIMMOTOR_h
#define _TRIMMOTOR_h

#include "arduino.h"
#include "LimitSwitch.h"

class TrimMotor
{

 private:
	 byte trimUpPin;
	 byte trimDownPin;
	 byte enablePin;
	
 public:

	 TrimMotor(byte TrimUpPin, byte TrimDownPin, byte EnablePin);
	 raiseMotor();
	 lowerMotor();
};

extern TrimMotor trimMotor;

#endif

