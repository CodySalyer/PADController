// 
// Constructor for Hall Effect Encoer object contains pin assignments for returning Encoder posisiton
// 

#include "SteeringMotorEncoder.h"

SteeringMotorEncoder::SteeringMotorEncoder(byte HallA, byte HallB, byte HallC)
{
	pinMode(HallA, INPUT);
	pinMode(HallB, INPUT);
	pinMode(HallC, INPUT);

	hallA = HallA;
	hallB = HallB;
	hallC = HallC;
}
