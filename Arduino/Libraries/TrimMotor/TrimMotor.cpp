// 
// Constructor for trim Motor object contains pin assignments for passing in trim motor commands
// 

#include "TrimMotor.h"


TrimMotor::TrimMotor(byte TrimUpPin, byte TrimDownPin, byte Enable)
{
	trimUpPin = TrimUpPin;
	trimDownPin = TrimDownPin;
	enablePin = EnablePin;
}
