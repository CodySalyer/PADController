// 
// Constructor for Motor object contains pin assignments for passing in motor commands
// 

#include "SteeringMotor.h"


SteeringMotor::SteeringMotor(byte EnablePin, byte DirectionPin, byte BrakePin, byte PotPin)
{
	enablePin = EnablePin;
	directionPin = DirectionPin;
	brakePin = BrakePin;
	potPin = PotPin;
}