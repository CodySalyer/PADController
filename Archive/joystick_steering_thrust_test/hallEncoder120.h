#pragma once
/* Things to delet from code*/

bool digitalRead(int pin) {
	return true;
}
int micros(void) {
	return 1;
}
int analogRead(int pin) {
	return 5;
}
#define INPUT 0
#define OUTPUT 1
void pinMode(int a, int b) {

}
class serial {
public:
	void print(char* message) {	}
	void print(char c) {	}
	void print(int a) { 	}
	void println(int value) {	}
};

/*+++++++++++++++++++++++++++++++*/

class Aarons_Encoder {
	/// ***************************************************************
	/// Auther: Aaron Sonderegger
	/// Date: Novemeber 2017
	/// ***************************************************************
	/// _________________________________________________________________________
	/// Using an encoder that has 3 hall effect sensors that are spaced at 120 
	/// [degrees] apart.  This is used to control the position of the motor
	/// _________________________________________________________________________
private:
	/*Things to Delete from Class*/
	serial Serial;
	/*++++++++++++++++++++++++++*/
	/// _________________________________________________________________________
	/// Variables used through out the code.  Using char since they take less 
	/// memory than int and because there the phases on the encoder are labeled 
	/// as A, B, and C.
	/// _________________________________________________________________________
#define A 'a'		// Phase A
#define B 'b'		// Phase B
#define C 'c'		// Phase C
#define AB 'd'		// Inbetween A and B
#define BC 'e'		// Inbetween B and C
#define CA 'f'		// Inbetween C and A
	/// Pins that are needed for the encoder
	int PIN_A = 13; 
	int PIN_B = 12;
	int PIN_C = 11;
	/// Flags that are used to help the controller process
	bool flagA = false;
	bool flagB = false;
	bool flagC = false;
	/// Things needed for code
	long pos = 0;
	int thresh = 2;		// Only needed for the analogReadA() Function.  
	char sensorOn;		// This is used for which sensor or phase is on
	char oldSensorOn;	// The last sensor or phase that was read
public:
	Aarons_Encoder(int pin_A, int pin_B, int pin_C) : 
		PIN_A(pin_A), 
		PIN_B(pin_B), 
		PIN_C(pin_C) 
	{	
		/// _________________________________________________________________________
		/// The constructed sets up the pin modes so it can be skipped in the setup 
		/// function.
		/// _________________________________________________________________________
		pinMode(pin_A, INPUT);
		pinMode(pin_B, INPUT);
		pinMode(pin_C, INPUT);
	}

	void readPinsD(void) {
		/// _________________________________________________________________________
		/// This function reads using the digital Read function.  This takes about 16
		/// microsencds to read 3 pins.  This is the prefurred method of reading the 
		/// sensors or phases.  
		/// _________________________________________________________________________
		flagA = digitalRead(PIN_A);			// sets it as true or false
		flagB = digitalRead(PIN_B);			// sets it as true or false
		flagC = digitalRead(PIN_C);			// sets it as true or false
		oldSensorOn = sensorOn;				// sets the old sensor to the last reading
		// This checks which sensor was just barely read
		if (flagA && !flagB && !flagC) {
			sensorOn = A;
		}
		else if (!flagA && flagB && !flagC) {
			sensorOn = B;
		}
		else if (!flagA && !flagB && flagC) {
			sensorOn = C;
		}
		else if (flagA && flagB && !flagC) {
			sensorOn = AB;
		}
		else if (!flagA && flagB && flagC) {
			sensorOn = BC;
		}
		else if (flagA && !flagB && flagC) {
			sensorOn = CA;
		}
	}

	void readPinsA(void) {
		/// _________________________________________________________________________
		/// This function reads using the anolog Read function.  This takes about 336 
		/// microseconds to read 3 pins.  This does same thing as the readPinsD() 
		/// function but reads with analogRead().  Not prefurred.  
		/// _________________________________________________________________________
		flagA = analogRead(PIN_A) > thresh ? true : false;
		flagB = analogRead(PIN_B) > thresh ? true : false;
		flagC = analogRead(PIN_C) > thresh ? true : false;
		oldSensorOn = sensorOn;
		if (flagA && !flagB && !flagC) {
			sensorOn = A;
		}
		else if (!flagA && flagB && !flagC) {
			sensorOn = B;
		}
		else if (!flagA && !flagB && flagC) {
			sensorOn = C;
		}
		else if (flagA && flagB && !flagC) {
			sensorOn = AB;
		}
		else if (!flagA && flagB && flagC) {
			sensorOn = BC;
		}
		else if (flagA && !flagB && flagC) {
			sensorOn = CA;
		}
	}

	int trackPositionS(void) {
		/// _________________________________________________________________________
		/// This function will follow what direction the pin is traveling and counts 
		/// the amount of steps it will take.  It uses the following pattern to 
		/// determine the what is positive and which is negative in direction to be 
		/// used.  
		///		+:		A -> AB -> B -> BC -> C -> CA
		///		-:		CA -> C -> BC -> B -> AB -> A
		/// This is the perferred method to track positions.  faster than the else if
		/// method
		/// _________________________________________________________________________

		switch (sensorOn) {
		case A:							// sensorOn check
			//Serial.print("Case A");
			switch (oldSensorOn) {
			case CA:
				++pos;
				break;
			case AB:
				--pos;
				break;
			case C:
				pos += 2;
				break;
			case B:
				pos -= 2;
				break;
			default:
				break;
			}
			break;
		case B:							// sensorOn check
			//Serial.print("Case B");
			switch (oldSensorOn) {
			case AB:
				++pos;
				break;
			case BC:
				--pos;
				break;
			case A:
				pos += 2;
				break;
			case C:
				pos -= 2;
				break;
			default:
				break;
			}
			break;
		case C:							// sensorOn check
			//Serial.print("Case C");
			switch (oldSensorOn) {
			case BC:
				++pos;
				break;
			case CA:
				--pos;
				break;
			case B:
				pos += 2;
				break;
			case A:
				pos -= 2;
				break;
			default:
				break;
			}
			break;
		case AB:						// sensorOn check
			//Serial.print("Case AB");
			switch (oldSensorOn) {
			case A:
				++pos;
				break;
			case B:
				--pos;
				break;
			case CA:
				pos += 2;
				break;
			case BC:
				pos -= 2;
				break;
			default:
				break;
			}
			break;
		case BC:						// sensorOn check
			//Serial.print("Case BC");
			switch (oldSensorOn) {
			case B:
				++pos;
				break;
			case C:
				--pos;
				break;
			case AB:
				pos += 2;
				break;
			case CA:
				pos -= 2;
				break;
			default:
				break;
			}
			break;
		case CA:						// sensorOn check
			//Serial.print("Case CA");
			switch (oldSensorOn) {
			case C:
				++pos;
				break;
			case A:
				--pos;
				break;
			case BC:
				pos += 2;
				break;
			case AB:
				pos -= 2;
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
	}

	int trackPositionEI(void) {
		/// _________________________________________________________________________
		/// This function will follow what direction the pin is traveling and counts 
		/// the amount of steps it will take.  It uses the following pattern to 
		/// determine the what is positive and which is negative in direction to be 
		/// used.  
		///		+:		A -> AB -> B -> BC -> C -> CA
		///		-:		CA -> C -> BC -> B -> AB -> A
		/// This uses else if statements.  Not the perferred method use 
		/// trackPositionS() instead of this one.
		/// _________________________________________________________________________
		if (sensorOn == A){
			if (oldSensorOn == CA) {
				++pos;
			}
			else if (oldSensorOn == AB) {
				--pos;
			}
			else if (oldSensorOn == C) {
				pos += 2;
			}
			else if (oldSensorOn == B){
				pos -= 2;
			}
		}
		else if (sensorOn == B) {
			if (oldSensorOn == AB) {
				++pos;
			}
			else if (oldSensorOn == BC) {
				--pos;
			}
			else if (oldSensorOn == A) {
				pos += 2;
			}
			else if (oldSensorOn == C) {
				pos -= 2;
			}
		}
		else if (sensorOn == C) {
			if (oldSensorOn == BC) {
				++pos;
			}
			else if (oldSensorOn == CA) {
				--pos;
			}
			else if (oldSensorOn == B) {
				pos += 2;
			}
			else if (oldSensorOn == A) {
				pos -= 2;
			}
		}
		else if (sensorOn == AB) {
			if (oldSensorOn == A) {
				++pos;
			}
			else if (oldSensorOn == B) {
				--pos;
			}
			else if (oldSensorOn == CA) {
				pos += 2;
			}
			else if (oldSensorOn == BC) {
				pos -= 2;
			}
		}
		else if(sensorOn == BC){
			if (oldSensorOn == B) {
				++pos;
			}
			else if (oldSensorOn == C) {
				--pos;
			}
			else if (oldSensorOn == AB) {
				pos += 2;
			}
			else if (oldSensorOn == CA) {
				pos -= 2;
			}
		}
		else if( sensorOn == CA){
			if (oldSensorOn == C) {
				++pos;
			}
			else if (oldSensorOn == A) {
				--pos;
			}
			else if (oldSensorOn == BC) {
				pos += 2;
			}
			else if (oldSensorOn == AB) {
				pos -= 2;
			}
		}
	}
	int getPosition(void) {
		/// _________________________________________________________________________
		/// This function returns the position of the pin that it's sitting at
		/// _________________________________________________________________________
		return pos;
	}

	int setPosition(int newPosition) {
		/// ________________________________________________________________________
		/// This function allows me to change the position of the Pin, If hit like a limit switch, changes to desired value
		/// _________________________________________________________________________
		pos = newPosition;
	}

	void highPin() {
		/// This function prints out what pin is currently on
		Serial.println(sensorOn);
	}

	void printMessage(auto message, int value) {
		/// _________________________________________________________________________
		/// This function allows me to print out something to do with the encoder
		/// _________________________________________________________________________
		Serial.print(message);
		Serial.println(value);
	}

	void timeFunction(auto Function) {
		/* this function times certain functions above that will be used a lot so I can opitimize code*/
		int t1, t2;
		if (Function == "trackPositionS") {
			// This took 42 microseconds at max and 4 microseconds a majority of the time using else if
			// This takes 12 microseconds at max and 8 microseconds a majority of the time using switch-case
			t1 = micros();
			trackPositionS();
			t2 = micros();
		}
		else if (Function == "trackPositionEI") {
			t1 = micros();
			trackPositionEI();
			t2 = micros();
		}
		else if (Function == "readPinsA") {
			t1 = micros();
			readPinsA();
			t2 = micros();
		}
		else if (Function == "readPinsD"){
			t1 = micros();
			readPinsD();
			t2 = micros();
		}
		else {
			Serial.print("Not Noticed");
		}
		Serial.print("Time to Perform");
		Serial.print(Function);
		Serial.print(": ");
		Serial.println(t2 - t1);
	}

	void getPlotData(void) {
		/// _________________________________________________________________________
		/// This function is ment to gather the data for the how the system behaives.
		/// The problem is with the Serial.print(), which takes to long and doesn't 
		/// allow for the microcontroller to count all the different time changes.
		/// _________________________________________________________________________
		int t1 = micros()*1000;
		while (1) {
			readPinsD();
			trackPositionS();
			Serial.print(micros()*1000 - t1);
			Serial.print(' ');
			Serial.println(pos);
		}
	}
};