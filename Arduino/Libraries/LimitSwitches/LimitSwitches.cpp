/* 
source file for LimitSwitches.h 
*/ 

#include "LimitSwitches.h"

LimitSwitches::LimitSwitches(byte UpLimitPin, byte DownLimitPin, byte LeftLimitPin, byte RightLimitPin)
{
	upLimitPin = UpLimitPin;
	downLimitPin = DownLimitPin;
	leftLimitPin = LeftLimitPin;
	rightLimitPin = RightLimitPin;

	pinMode(upLimitPin, INPUT);
	pinMode(downLimit, INPUT);
	pinMode(leftLimitPin, INPUT);
	pinMode(rightLimitPin, INPUT);
}
LimitSwtiches::update()
{
	upStatus = digitalRead(upLimitPin);
	downStatus = digitalRead(downLimitPin);
	leftStatus = digitalRead(leftLimitPin);
	rightStatus = digitalRead(rightLimitPin);
}
// Returns the status of the top limit switch
bool LimitSwtiches::getUpStatus()
{
	update();
	return upStatus;
}
// Returns the status of the down limit switch
bool LimitSwtiches::getDownStatus()
{
	update();
	return downStatus;
}
// Returns the status of the left limit switch
bool LimitSwtiches::getLeftStatus()
{
	update();
	return leftStatus;
}
// Returns the status of the right limit switch
bool LimitSwtiches::getRightStatus()
{
	update();
	return rightStatus;
}