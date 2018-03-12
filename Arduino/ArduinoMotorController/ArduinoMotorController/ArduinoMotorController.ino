/*
 Name:		ArduinoMotorController.ino
 Created:	2/21/2018 3:21:51 PM
 Author:	C Salyer
*/

#include <SteeringMotorEncoder.h>
#include <SteeringMotor.h>

SteeringMotor RearSteeringMotor(4, 3, 2, 9); 
//SteeringMotorEncoder FrontSteeringMotor(-, -, -, -);

SteeringMotorEncoder RearSteeringMotorEncoder(13, 12, 11);
//SteeringMotorEncoder FrontSteeringMotorEncoder(-, -, -);


void setup() 
{

}

// the loop function runs over and over again until power down or reset
void loop() 
{
  
}
