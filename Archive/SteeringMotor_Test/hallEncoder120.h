#pragma once
/* Things to delet from code*/

/*+++++++++++++++++++++++++++++++*/

class Aarons_Encoder {
	/* Using an encoder that has 3 hall effect sensors and that are read 
	4 times per revolution.  24 readings/360 degrees*/
private:
	/*Things to Delete from Class*/

	/*++++++++++++++++++++++++++*/
#define A 'a'
#define B 'b'
#define C 'c'
#define AB 'd'
#define BC 'e'
#define CA 'f'
	int PIN_A = 13;
	int PIN_B = 12;
	int PIN_C = 11;
	bool flagA = false;
	bool flagB = false;
	bool flagC = false;
	long pos = 0;
	int thresh = 2;
	char sensorOn;
	char oldSensorOn;
public:
	/* Defaults to PIN_A = 13, PIN_B = 12, PIN_C = 11.
	This constructor assigns pins to where user would like them to be on*/
	Aarons_Encoder(int pin_A, int pin_B, int pin_C) : 
		PIN_A(pin_A), 
		PIN_B(pin_B), 
		PIN_C(pin_C) {	}

	/* This function reads using the digital Read function.  This takes about 16 microsencds to read 3 pins*/
	void readPinsD(void) {
		flagA = digitalRead(PIN_A);
		flagB = digitalRead(PIN_B);
		flagC = digitalRead(PIN_C);
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

	/* This function reads using the anolog Read function.  This takes about 336 microseconds to read 3 pins*/
	void readPinsA(void) {
		flagA = analogRead(PIN_A) > thresh ? true : false;
		flagB = analogRead(PIN_B) > thresh ? true : false;
		flagC = analogRead(PIN_C) > thresh ? true : false;
		if (flagA && !flagB && !flagC) {
			oldSensorOn = sensorOn;
			sensorOn = A;
		}
		else if (!flagA && flagB && !flagC) {
			oldSensorOn = sensorOn;
			sensorOn = B;
		}
		else if (!flagA && !flagB && flagC) {
			oldSensorOn = sensorOn;
			sensorOn = C;
		}
		else if (flagA && flagB && !flagC) {
			oldSensorOn = sensorOn;
			sensorOn = AB;
		}
		else if (!flagA && flagB && flagC) {
			oldSensorOn = sensorOn;
			sensorOn = BC;
		}
		else if (flagA && !flagB && flagC) {
			oldSensorOn = sensorOn;
			sensorOn = CA;
		}
	}

	/* This function will follow what direction the pin is traveling and counts the amount of steps it will take*/
  int trackPositionS(void) {
    /*+: A -> AB -> B -> BC -> C -> CA
      -: CA -> C -> BC -> B -> AB -> A*/
    switch (sensorOn) {
    case A:
//      Serial.print("Case A");
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
    case B:
//      Serial.print("Case B");
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
    case C:
//      Serial.print("Case C");
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
      /*+: A -> AB -> B -> BC -> C -> CA
      -: CA -> C -> BC -> B -> AB -> A*/
    case AB:
//      Serial.print("Case AB");
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
    case BC:
//      Serial.print("Case BC");
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
    case CA:
//      Serial.print("Case CA");
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


/* This Function tracks the position based on which hall effect sensor is sensed. Same as the one above but 
   but uses else-if statements.  This maybe faster than switches*/
  int trackPositionEI(void) {
    /*+: A -> AB -> B -> BC -> C -> CA
    -: CA -> C -> BC -> B -> AB -> A*/
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
      /*+: A -> AB -> B -> BC -> C -> CA
      -: CA -> C -> BC -> B -> AB -> A*/
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
      /*+: A -> AB -> B -> BC -> C -> CA
      -: CA -> C -> BC -> B -> AB -> A*/
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
      /*+: A -> AB -> B -> BC -> C -> CA
      -: CA -> C -> BC -> B -> AB -> A*/
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
      /*+: A -> AB -> B -> BC -> C -> CA
      -: CA -> C -> BC -> B -> AB -> A*/
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


	/* This function returns the position of the pin that it's sitting at*/
	int getPosition(void) {
		return pos;
	}

	/* This function allows me to change the position of the Pin, If hit like a limit switch, changes to desired value*/
	int setPosition(int newPosition) {
		pos = newPosition;
	}

	/* This function prints out what pin is currently on*/
	void highPin() {
		Serial.println(sensorOn);
	}

	/* This function allows me to print out something to do with the encoder*/
	void printMessage(String message, int value) {
		Serial.print(message);
		Serial.println(value);
	}

	/* this function times certain functions above that will be used a lot so I can opitimize code*/
  void timeFunction(String Function) {
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
    else{
      Serial.print("Not Noticed");
    }
    Serial.print("Time to Perform ");
    Serial.print(Function);
    Serial.print(": ");
    Serial.println(t2 - t1);
  }


	void getPlotData(void) {
		int t1 = millis();
		while (1) {
			readPinsD();
      trackPositionS();
			Serial.print(millis() - t1);
			Serial.print(' ');
			Serial.println(pos);
		}
	}
};
