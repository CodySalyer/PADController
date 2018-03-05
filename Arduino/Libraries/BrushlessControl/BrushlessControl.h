#define CW			true
#define CCW			false
#define _BRAKE		true
#define NO_BRAKE	false
#define ENABLE		true
#define NOT_ENABLE	false

#pragma once

class BrushlessControl 
{
private:

	// default values used if default constructor is used
	int enablePin = 7;
	int brakePin = 13;
	int directionPin = 8;
	int speedPin = 9;
	bool dir;
	int motorSpeed = 0;

public:

	/*Constructors for brushlessControl Object*/
	/*default constructor*/
	BrushlessControl() {}

	/*constructor that overwrites pin defaults*/
	BrushlessControl(int _enablePin, int _brakePin, int _directionPin, int _speedPin)
	{
		// maps inputs to private values
		enablePin = _enablePin;
		brakePin = _brakePin;
		directionPin = _directionPin;
		speedPin = _speedPin;
	
		//assigns pin modes based on the constructor
		pinMode(directionPin, OUTPUT);
		pinMode(brakePin, OUTPUT);
		pinMode(enablePin, OUTPUT);
		pinMode(speedPin, OUTPUT);
	}

	/*Method that maintains the motor conditions possible update script*/
	void runMotor(void) 
	{
		digitalWrite(directionPin, dir);
		digitalWrite(enablePin, ENABLE);
		digitalWrite(brakePin, NO_BRAKE);
		analogWrite(speedPin, motorSpeed);
	}

	/*Sets the motor speed (rewrite) */
	void setMotorSpeed(int _speed) //consider combining speed and direction so the speed range is -inf to inf with sign determining direction
	{
		if (_speed > 255) 
		{
			motorSpeed = 255;
		}

		else 
		{
			motorSpeed = _speed;
		}
	}

	/*turns off motor but does not set the brake*/
	void coastMotor(void) 
	{
		digitalWrite(enablePin, NOT_ENABLE);
	}

	/*Stops the motor and enables brake pin*/
	void stopMotor(void) 
	{
		digitalWrite(enablePin, NOT_ENABLE);
		digitalWrite(brakePin, _BRAKE);
	}

	/*Set the direction of the motor CW=true*/
	void setDirection(bool val) 
	{
		dir = val;
	}

	/* Returns the direction bool true = ?*/
	bool getDirection(void) 
	{
		return dir;
	}

	/*Returns the motor speed currently set*/
	int getSpeed(void) 
	{
		return motorSpeed;
	}
};
