// TrimMotor.h

#ifndef _TRIMMOTOR_h
#define _TRIMMOTOR_h

#include "arduino.h"

class TrimMotor
{

 protected:

 public:
	 byte trimUpPin;
	 byte trimDownPin;
	 byte enablePin;
	
	 TrimMotor(byte TrimUpPin, byte TrimDownPin, byte EnablePin);
};

extern TrimMotor trimMotor;

#endif

