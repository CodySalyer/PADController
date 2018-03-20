// 
// Constructor for Motor object contains pin assignments for passing in motor commands
// 

#include "SteeringMotor.h"

SteeringMotor::SteeringMotor(byte EnablePin, byte DirectionPin, byte BrakePin, byte PotPin)
{
	pinMode(EnablePin, OUTPUT);
	pinMode(DirectionPin,OUTPUT);
	pinMode(BrakePin,OUTPUT);
	pinMode(PotPin,OUTPUT);

	enablePin = EnablePin;
	directionPin = DirectionPin;
	brakePin = BrakePin;
	potPin = PotPin;
}
