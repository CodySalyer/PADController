/* 
source file for SteeringMotor.h 
*/ 

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

	enabled = false;
	brakeEngaged = false;
	motorDirection = false;
}
SteeringMotor::Enabled(bool enableMotor)
{
	if (enableMotor == true)
	{
		digitalWrite(EnablePin, TRUE);
		enabled = true;
	}
	else
	{
		digitalWrite(EnablePin, FALSE);
		enabled = false;
	}
}
SteeringMotor::EngageBrake(bool brakeState)
{
	if (brakeState == true)
	{
		digitalWrite(brakePin, TRUE);
		brakeEngaged = true;
	}
	else
	{
		digitalWrite(brakePin, FALSE);
		brakeEngaged = false;
	}
}
SteeringMotor::SetSpeed(int speed)
{
	// Based on the speed of the motor being positive or negative it sets the direction
	bool direction;
	if (speed < 0)
	{
		direction = true;
		speed = abs(speed);
	}
	else
	{
		direction = false;
	}

	// sets the direction of the motor by toggling direction pin
	if (direction == true) 
	{
		digitalWrite(directionPin, TRUE);
		motorDirection = true;
	}
	else
	{
		digitalWrite(directionPin, FALSE);
		motorDirection = false;
	}

	// Sets the pwm for the speed of the motor
	if (speed > 255)
	{
		analogWrite(speedPin, 255);
	}
	else
	{
		analogWrite(speedPin, speed);
	}
}