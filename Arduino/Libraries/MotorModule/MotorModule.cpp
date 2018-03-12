// 
// Constructor for Motor object contains pin assignments for passing in motor commands
// 

#include "Motor.h"


MotorModule::MotorModule(byte EnablePin, byte DirectionPin, byte BrakePin, byte PotPin)
{
	enablePin = EnablePin;
	directionPin = DirectionPin;
	brakePin = BrakePin;
	potPin = PotPin;
}
