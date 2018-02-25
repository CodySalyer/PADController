#pragma once
void pinMode(int a, bool b) {

}
void digitalWrite(int a, bool b) {

}
void delay(int a) {

}
#define INPUT 0
#define OUTPUT 1
#define HIGH 1
#define LOW 0
struct String
{
	char* t;
};

class relayBoard {
	/// ***************************************************************
	/// Auther: Aaron Sonderegger
	/// Date: Novemeber 2017
	/// ***************************************************************
	/// _________________________________________________________________________

	/// This class is specifically for the PADS relay board switch used for 
	/// trimming up and trimming down the actuator, and turning on and off the 
	/// E~TECH motor.  
	/// _________________________________________________________________________

private:
	/// _________________________________________________________________________
	/// These pins are for the trim actuator and the ETECH motor.  Default as 13, 
	/// 12, and 11 for no specific reason.  Constructur will assign to what the 
	/// user defines.
	/// _________________________________________________________________________
	const int upPin = 13;
	const int downPin = 12;
	const int etechPin = 11;
	bool flagUp = false;
	bool flagDown = false;
public:
	relayBoard(int etechPin_, int upPin_, int downPin_) :
		etechPin(etechPin_), upPin(upPin_), downPin(downPin_) 
	{
		/// _________________________________________________________________________
		/// This constructor sets up the pins so it can be avoided in the 
		/// setup() function of arduino.  The pins are written to high because 
		/// it will keep them closed.  When the arduino has no power they are closed.  
		/// if both pins are wrote to be LOW then the big actuator relay board will 
		/// short
		/// _________________________________________________________________________
		pinMode(etechPin_, OUTPUT);
		pinMode(upPin_, OUTPUT);
		pinMode(downPin_, OUTPUT);
		digitalWrite(etechPin_, HIGH);		// Needs to be HIGH so motor doesn't turn on
											// with out users permission.
		digitalWrite(upPin_, HIGH);			// MUST be HIGH (DO NOT CHANGE)
		digitalWrite(downPin_, HIGH);		// MUST be HIGH (DO NOT CHANGE)
	}
	void runActuator(String command) {
		/// _________________________________________________________________________
		/// This function is for changing what direction the actuator is moving
		/// _________________________________________________________________________

		if (command == "up" || command == "UP" || command == "Up") {
			if (!flagUp) {
				digitalWrite(downPin, HIGH);	// Closes the downPin
				delay(500);					// just to ensure the switch is closed before opening the other
				flagUp = true;
				flagDown = false;
			}
			digitalWrite(upPin, LOW);		// Opens the upPin
		}
		else if (command == "down" || command == "Down" || command == "DOWN") {
			if (!flagDown) {
				digitalWrite(upPin, HIGH);		// Closes the upPin
				delay(500);					// just to ensure the switch is closed before opening the other
				flagUp = false;
				flagDown = true;
			}
			digitalWrite(downPin, LOW);		// Opens the downPin
		}
		else{
			flagDown = false;
			flagUp = false;
			digitalWrite(upPin, HIGH);		// Closes upPin
			digitalWrite(downPin, HIGH);	// closes downPin
		}
	}
	void turnEtechON(void) {
		digitalWrite(etechPin, LOW);
	}
	void turnEtechOFF(void) {
		digitalWrite(etechPin, HIGH);
	}
};