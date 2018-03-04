#include <HallEncoder.h>
#include <BrushlessControl.h>
#include <Error.h>

BrushlessControl motor1;
HallEncoder encoder1;

void setup()
{
	Serial.begin(9600);
	Serial.println("Hall Effect Test");
}

void loop()
{
	motor1.coastMotor();

	int currentPosition = encoder1.trackPositionS();
	Serial.print("Hall Position: ");
	Serial.println(currentPosition);
}
