// HallEffectEncoder.h

#ifndef _HALLEFFECTENCODER_h
#define _HALLEFFECTENCODER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class HallEffectEncoder
{

 private:
	 byte hallA;
	 byte hallB;
	 byte hallC;

	 char sensorTripped;
	 char previousSensorTripped;

	 bool flagA = false;
	 bool flagB = false;
	 bool flagC = false;

	 void readPins(void);
	 int position;

 public:
	 HallEffectEncoder(byte HallA, byte HallB, byte HallC);
	 int updatePosition(void);
	 int getPosition();
	 setPosition(int newPosition);
};

extern HallEffectEncoder hallEffectEncoder;

#endif

