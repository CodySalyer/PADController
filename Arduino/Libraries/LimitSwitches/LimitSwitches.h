// LimitSwitches.h

#ifndef _LIMITSWITCHES_h
#define _LIMITSWITCHES_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class LimitSwitches
{

 private:
	 byte upLimitPin;
	 byte downLimitPin;
	 byte leftLimitPin;
	 byte rightLimitPin;

	 bool upStatus;
	 bool downStatus;
	 bool leftStatus;
	 bool rightStatus;

	update();

 public:
	 LimitSwitches(byte UpLimitPin, byte DownLimitPin, byte LeftLimitPin, byte RightLimitPin);
	 
	 bool getUpStatus();
	 bool getDownStatus();
	 bool getLeftStatus();
	 bool getRightStatus();
};

extern LimitSwitches limitSwitches;

#endif

