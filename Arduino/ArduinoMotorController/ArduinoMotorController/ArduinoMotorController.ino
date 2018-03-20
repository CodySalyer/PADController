/*
 Name:		ArduinoMotorController.ino
 Created:	2/21/2018 3:21:51 PM
 Author:	C Salyer
*/

#include <TrimMotor.h>
#include <Joystick.h>
#include "Arduino.h"
#include <SteeringMotorEncoder.h>
#include <SteeringMotor.h>

int lala = 5;
/*Steering Motor constructors:
(Enable Pin, Direction Pin, Brake Pin, Potentiometer Pin) */
SteeringMotor RearSteeringMotor(4, 3, 2, 9); 
//SteeringMotorEncoder FrontSteeringMotor(-, -, -, -);

/*Motor Encoder constructors:
(HallA pin, HallB pin HallC pin) */
SteeringMotorEncoder RearSteeringMotorEncoder(13, 12, 11);
//SteeringMotorEncoder FrontSteeringMotorEncoder(-, -, -);

/*Trim Motor constructor:
(Trim up pin, trim down pin, enable pin) */
TrimMotor RearTrimMotor(11, 12, 5);
//TrimMotor FrontTrimMotor(-, -, -);

/* Serial Communication Constructor
Defines the serial communication between this and the master*/
//SerialCommunication Serialdata();

void setup() 
{
	Serial.begin(9600);
	Serial.print(RearSteeringMotor.enablePin);
}

// the loop function runs over and over again until power down or reset
void loop() 
{
	delay(500);
	Serial.print(RearSteeringMotor.enablePin);
}
