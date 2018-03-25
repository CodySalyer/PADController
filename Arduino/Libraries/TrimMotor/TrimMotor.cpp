// 
// Constructor for trim Motor object contains pin assignments for passing in trim motor commands
// 

#include "TrimMotor.h"
#include "LimitSwitch.h"

TrimMotor::TrimMotor(byte TrimUpPin, byte TrimDownPin, byte EnablePin, LimitSwitch& limitSwtich)
{
	pinMode(TrimUpPin, OUTPUT);
	pinMode(TrimDownPin, OUTPUT);
	pinMode(EnablePin, OUTPUT);

	trimUpPin = TrimUpPin;
	trimDownPin = TrimDownPin;
	enablePin = EnablePin;
}
TrimMotor::raiseMotor() 
{
	// set pin to raise the boat
	// check for limit switch
	if (limitSwitch.up == false)
	{
		// set motor to rise
	}
	else
	{
		// set motor to stop
	}
}
TrimMotor::lowerMotor()
{
	// sets pin to lower motor
	// checks for limit switch while running
	if (limitSwitch.down == false)
	{
		// set the motor to lower
	}
	else
	{
		// stop the motor
	}
}