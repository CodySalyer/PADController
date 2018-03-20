// 
// Constructor for trim Motor object contains pin assignments for passing in trim motor commands
// 

#include "TrimMotor.h"

TrimMotor::TrimMotor(byte TrimUpPin, byte TrimDownPin, byte EnablePin)
{
	pinMode(TrimUpPin, OUTPUT);
	pinMode(TrimDownPin, OUTPUT);
	pinMode(EnablePin, OUTPUT);

	trimUpPin = TrimUpPin;
	trimDownPin = TrimDownPin;
	enablePin = EnablePin;
}
