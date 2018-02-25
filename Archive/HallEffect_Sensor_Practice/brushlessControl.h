#pragma once
/* things to delete */
void digitalWrite(int a, bool r){}
void analogWrite(int b, int s) {}
void pinMode(int a, bool e) {}
#define OUTPUT true

/* ++++++++++++++++++ */

class brushlessControl {
	/// ***************************************************************
	/// Auther: Aaron Sonderegger
	/// Date: Novemeber 2017
	/// ***************************************************************
	/// _________________________________________________________________________
	/// This class is used to control the PADS brushless motor.  
	/// _________________________________________________________________________
private:
	/// _________________________________________________________________________
	/// These have been measured and defined from the manufacturors specification
	/// http://www.anaheimautomation.com/manuals/brushless/L010233%20-%20MDC100-050101%20Users%20Guide.pdf
	/// _________________________________________________________________________
#define BRAKE true
#define NO_BRAKE false
#define ENABLE true
#define NOT_ENABLE false
	int enablePin = 7;
	int brakePin = 13;
	int directionPin = 8;
	int speedPin = 9;				// NEEDS to be a PWM pin
	bool dir;
	int motorSpeed = 0;
public:
	brushlessControl(int _enablePin, int _brakePin, int _directionPin, int _speedPin) :
		enablePin(_enablePin),
		brakePin(_brakePin),
		directionPin(_directionPin),
		speedPin(_speedPin)
	{
		/// _________________________________________________________________________
		/// The constructor assigns the pins used.  This sets up the pinMode for the 
		/// pins so it doesn't need to happen in the setup function.
		/// _________________________________________________________________________
		pinMode(directionPin, OUTPUT);
		pinMode(brakePin, OUTPUT);
		pinMode(enablePin, OUTPUT);
		pinMode(speedPin, OUTPUT);
	}
	void runMotor(void) {
		/// _________________________________________________________________________
		/// This function turns the motor on, sets the direction, and sets the speed
		/// _________________________________________________________________________
		digitalWrite(directionPin, dir);
		digitalWrite(enablePin, ENABLE);
		digitalWrite(brakePin, NO_BRAKE);
		analogWrite(speedPin, motorSpeed);
	}

	void setMotorSpeed(int _speed) {
		/// _________________________________________________________________________
		/// This function sets the motor speed to a max of 255 for the PWM signal.  
		/// _________________________________________________________________________
		if (_speed > 255) {
			motorSpeed = 255;
		}
		else {
			motorSpeed = _speed;
		}
	}
	void coastMotor(void) {
		/// _________________________________________________________________________
		/// This function lets the motor coast to a stop with out using the break.  
		/// the analogWrite() function isn't needed but it's for extra precaution.
		/// _________________________________________________________________________
		analogWrite(speedPin, 0);
		digitalWrite(enablePin, NOT_ENABLE);
	}
	void stopMotor(void) {
		/// _________________________________________________________________________
		/// This function uses the brake of the motor to stop it's motion.
		/// _________________________________________________________________________
		analogWrite(speedPin, 0);
		digitalWrite(enablePin, NOT_ENABLE);
		digitalWrite(brakePin, BRAKE);
	}

	void setDirection(bool val) {
		dir = val;
	}

	bool getDirection(void) {
		return dir;
	}
	int getSpeed(void) {
		return motorSpeed;
	}
};