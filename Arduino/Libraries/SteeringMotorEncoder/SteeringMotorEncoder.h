// SteeringMotorEncoder.h

#ifndef _STEERINGMOTORENCODER_h
#define _STEERINGMOTORENCODER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class SteeringMotorEncoder
{

 protected:

 public:
	 byte hallA;
	 byte hallB;
	 byte hallC;

	 SteeringMotorEncoder(byte HallA, byte HallB, byte HallC);
};

extern SteeringMotorEncoder steeringMotorEncoder;

#endif

