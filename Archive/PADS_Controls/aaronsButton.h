#pragma once

int digitalRead(int a) {
	return 1;
}
void pinMode(int a, bool b) {

}
#define HIGH 1
#define LOW 0
#define INPUT 1
#define OUTPUT 2

class aaronsButton {
	/// ***************************************************************
	/// Auther: Aaron Sonderegger
	/// Date: Novemeber 2017
	/// ***************************************************************
private:
#define maxMode 5
	int buttonPin;
	bool buttonFlag = false;
	int state = 0;
public:
	aaronsButton(int _buttonPin) :
		buttonPin(_buttonPin) 
	{
		/// _________________________________________________________________________
		/// This constructs the buttonPin and does the setup for it.
		/// _________________________________________________________________________
		pinMode(_buttonPin, INPUT);
	}
	void readButton_(void) {
		/// _________________________________________________________________________
		/// This function reads the button for every time it is pushed.  If the 
		/// button is held down it reads it once then moves on. Button is for 
		/// changing different states. 
		/// _________________________________________________________________________
		if (digitalRead(buttonPin) && !buttonFlag) {
			++state;
			buttonFlag = true;
		}
		else if ( !digitalRead(buttonPin) ) {
			buttonFlag = false;
		}
		if (state > maxMode) {
			state = 0;
		}
	}
	int getState(void) {
		return state;
	}
};