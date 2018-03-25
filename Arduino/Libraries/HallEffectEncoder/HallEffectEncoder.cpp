/*
source file for HallEffectEncoder object
*/

#include "HallEffectEncoder.h"

#define A  'a'
#define B  'b'
#define C  'c'
#define AB 'd'
#define BC 'e'
#define CA 'f'

// Constructor for halleffectEncoer ( USE INTERUPT CAPABLE PORTS )
HallEffectEncoder::HallEffectEncoder(byte HallA, byte HallB, byte HallC)
{
	pinMode(HallA, INPUT);
	pinMode(HallB, INPUT);
	pinMode(HallC, INPUT);

	hallA = HallA;
	hallB = HallB;
	hallC = HallC;

	attachInterrupt(digitalPinToInterrupt(hallA), updatePosition(), CHANGE);
	attachInterrupt(digitalPinToInterrupt(hallB), updatePosition(), CHANGE);
	attachInterrupt(digitalPinToInterrupt(hallC), updatePosition(), CHANGE);

	position = 0;
}
// Private method that reads the halleffect pins and determines position
void HallEffectEncoder::readPins()
{
	flagA = digitalRead(PIN_A);
	flagB = digitalRead(PIN_B);
	flagC = digitalRead(PIN_C);

	previousSensorTripped = sensorTripped;

	if (flagA && !flagB && !flagC)
	{
		sensorTripped = A;
	}
	else if (!flagA && flagB && !flagC)
	{
		sensorTripped = B;
	}
	else if (!flagA && !flagB && flagC)
	{
		sensorTripped = C;
	}
	else if (flagA && flagB && !flagC)
	{
		sensorTripped = AB;
	}
	else if (!flagA && flagB && flagC)
	{
		sensorTripped = BC;
	}
	else if (flagA && !flagB && flagC)
	{
		sensorTripped = CA;
	}
}
// This uses the interupt ports to track the change in position
int HallEffectEncoder::updatePosition()
{
	readPins();
	/*+: A -> AB -> B -> BC -> C -> CA
	-: CA -> C -> BC -> B -> AB -> A*/
	switch (sensorTripped)
	{
	case A:
		//Serial.print("Case A");
		switch (previousSensorTripped)
		{
		case CA:
			++position;
			break;

		case AB:
			--position;
			break;

		case C:
			position += 2;
			break;

		case B:
			position -= 2;
			break;

		default:
			break;
		}
		break;

	case B:
		// Serial.print("Case B");
		switch (previousSensorTripped)
		{
		case AB:
			++position;
			break;

		case BC:
			--position;
			break;

		case A:
			position += 2;
			break;

		case C:
			position -= 2;
			break;

		default:
			break;
		}
		break;

	case C:
		// Serial.print("Case C");
		switch (previousSensorTripped)
		{
		case BC:
			++position;
			break;

		case CA:
			--position;
			break;

		case B:
			position += 2;
			break;

		case A:
			position -= 2;
			break;

		default:
			break;
		}
		break;

		/*+: A -> AB -> B -> BC -> C -> CA
		-: CA -> C -> BC -> B -> AB -> A*/

	case AB:
		// Serial.print("Case AB");
		switch (previousSensorTripped)
		{
		case A:
			++position;
			break;

		case B:
			--position;
			break;

		case CA:
			position += 2;
			break;

		case BC:
			position -= 2;
			break;

		default:
			break;
		}
		break;

	case BC:
		// Serial.print("Case BC");
		switch (previousSensorTripped)
		{
		case B:
			++position;
			break;

		case C:
			--position;
			break;

		case AB:
			position += 2;
			break;

		case CA:
			position -= 2;
			break;

		default:
			break;
		}
		break;

	case CA:
		// Serial.print("Case CA");
		switch (previousSensorTripped)
		{
		case C:
			++position;
			break;

		case A:
			--position;
			break;

		case BC:
			position += 2;
			break;

		case AB:
			position -= 2;
			break;

		default:
			break;
		}
		break;

	default:
		break;
	}


}
// Method that returns the current encoder posisiton.
int HallEffectEncoder::getPosition()
{
	return position;
}
void HallEffectEncoder::setPosition(int newPosition)
{
	position = newPosition;
}
