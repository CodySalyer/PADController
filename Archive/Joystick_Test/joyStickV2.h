#pragma once
/* **********************
Delete before use
*************************/
#include <math.h>
#define OUTPUT 0
#define INPUT 1
#define HIGH 1
#define LOW 0
void digitalWrite(int a, int b) { }
void analogWrite(int a, int b) { }
int analogRead(int a) { return 1; }
void pinMode(int a, bool b) { }
int abs(int a) { return 1; }
int map(int a, int b, int c, int d, int e) { return 1; }

class joystick3 {
	/// ***************************************************************
	/// Auther: Aaron Sonderegger
	/// Date: Novemeber 2017
	/// ***************************************************************
	using aaron = double;				// used incase I want to use ints, floats, double, etc...
										/// _________________________________________________________________________
										/// This joystick if for an x, y, theta joystick.  This will compute mainly
										/// an angle and magnitude from the x, y readings.
										/// _________________________________________________________________________
private:
	/// _________________________________________________________________________
	/// Values that work great for the joystick
	/// _________________________________________________________________________
	// TODO: Get actual joystick from Nicolas and measure the valuse to  be used
//#define xThresh 25				// creates a dead zone for the joystick x
//#define x0 520					// When x is unmoved
//#define xMax 1023				// Max x value reading from raw data
//#define xMin 0					// Min x value reading from raw data
//#define yThresh 25				// creates a dead zone for the joystick y
//#define y0 487					// When y is unmoved
//#define yMax 1023				// Max y value reading from raw data
//#define yMin 0					// Min y value reading from raw data
//#define thetaThresh 50			// creates a dead zone for the joystick theta
//#define theta0 64				// When y is unmoved
//#define thetaMax 620			// Max y value reading from raw data
//#define thetaMin 0				// Min y value reading from raw data

#define xThresh 25				// creates a dead zone for the joystick x
#define x0 513					// When x is unmoved
#define xMax 790				// Max x value reading from raw data
#define xMin 224					// Min x value reading from raw data
#define yThresh 25				// creates a dead zone for the joystick y
#define y0 508					// When y is unmoved
#define yMax 800				// Max y value reading from raw data
#define yMin 220					// Min y value reading from raw data
#define thetaThresh 20			// creates a dead zone for the joystick theta
#define theta0 56				// When y is unmoved
#define thetaMax 620			// Max y value reading from raw data
#define thetaMin 0				// Min y value reading from raw data

#define FORWARD 255				// This will put out a voltage of 5V for the E~TECH Motor
	// This is full throttle
#define NEUTRAL 127				// This will put out a voltage of 2.5V for the E~TECH Motor
	// This will sit at Neutral 
#define REVERSE 0				// This will put out a voltage of 0V for the E~TECH Motor
	// This will sit at full reverse throttle
#define coordinatePos 511
#define coordinateNeg 512
	/// PINS for the micro control to use
	int xPin = 0;
	int yPin = 1;
	int thetaPin = 2;
	/// varables used to compute values.  Do the division here to same time when computing
	/// dividing is more expensive than multiplication for micro controller
	const aaron ANGLEMAX = 1.5708;		// 90 [degrees]
	const aaron ANGLETHRESH = 1.2217;	// 70 [degrees]
	aaron X = 0;						// X variable start at Neutral
	aaron Y = 0;						// Y variable start at Neutral
	aaron Theta = 0;					// Theta variable start at Neutral
	const aaron radtoDeg = 180 / 3.1416;// 180/pi, used to convert from rad to deg
	aaron angle = 0.0;					// Angle variable that is used to control position of motor
	aaron magnitude = 127;				// Throttle variable to control the thrust

	aaron oldX = 0;						// variable used for the last reading
	aaron oldY = 0;						// variable used for the last reading
	aaron oldTheta = 0;					// variable used for the last reading
public:
	joystick3(int _xPin, int _yPin, int _theta) :
		xPin(_xPin), yPin(_yPin), thetaPin(_theta)
	{
		/// _________________________________________________________________________
		/// This is the constructer for the joystick.  This defines the pin as input 
		/// for the microcontroller.  Doesn't have to be done in the setup function.
		/// Doesn't necissarily need to happen
		/// _________________________________________________________________________
		pinMode(_xPin, INPUT);
		pinMode(_yPin, INPUT);
		pinMode(_theta, INPUT);
	}
	void RawInformation() {
		/// _________________________________________________________________________
		/// This function just prints out the raw information of the analogRead 
		/// function.  This is to be used when finding the #define values above.  
		/// Have to open the serial monitor to see the values.  
		/// _________________________________________________________________________
		Serial.print("X: ");
		Serial.print(analogRead(xPin));
		Serial.print(" Y: ");
		Serial.print(analogRead(yPin));
		Serial.print(" Theta: ");
		Serial.println(analogRead(thetaPin));
	}

	void readJoystick(void) {
		/// _________________________________________________________________________
		/// This function goes through and reads the pins and maps them to the values
		/// that are usable for the joystick.  This is where the dead-zone is created
		/// and the max and min values are set.
		/// _________________________________________________________________________
		oldX = X;
		oldY = Y;
		oldTheta = Theta;
		X = analogRead(xPin);						// Reads xPin
		Y = analogRead(yPin);						// Reads yPin
		Theta = analogRead(thetaPin);				// Reads thetaPin
													// Checks x dead-zone
		if (abs(X - x0) < xThresh) {
			X = x0;
		}
		X = X >= x0 ?								// if Statement 
			map(X, x0, xMax, 0,-coordinateNeg) :	// if True 
			map(X, x0, xMin, 0, coordinatePos);		// if False 
													// Checks x dead-zone
		if (abs(Y - y0) < yThresh) {
			Y = y0;
		}
		Y = Y >= y0 ?								// if Statement
			map(Y, y0, yMax, 0, -coordinateNeg) :    // if True
			map(Y, y0, yMin, 0, coordinatePos);     // if False
													// Checks x dead-zone
		if (abs(Theta - theta0) < thetaThresh) {
			Theta = theta0;
		}
		Theta = Theta >= theta0 ?					// if Statement
			map(Theta, theta0, thetaMax, 0, -coordinateNeg ) :
			map(Theta, theta0, thetaMin, 0, coordinatePos);
		// Correct any mapping issues
		if (X < -coordinateNeg) {
			X = -coordinateNeg;
		}
		else if (X > coordinatePos) {
			X = coordinatePos;
		}
		if (Y < -coordinateNeg) {
			Y = -coordinateNeg;
		}
		else if (Y > coordinatePos) {
			Y = coordinatePos;
		}
		if (Theta < -coordinateNeg) {
			Theta = -coordinateNeg;
		}
		else if (Theta > coordinatePos) {
			Theta = coordinatePos;
		}
		// TODO: Delete the ignoreTheta() or comment out for the actual program
		ignoreTheta();
		computeAngle();					// Computes the angle.  See below
		computeMagnitude();				// Computes the magnitude. See below
	}

	void computeMagnitude(void) {
		/// _________________________________________________________________________
		/// This uses the magnitude of the joystick loaction.  When in nuetral it 
		/// should not be anything else than 127.  It shouldn't ever go above 255 or 
		/// below 0.  Not sure why but the atan() function angle that is returned is 
		/// not a friendly value here.  Works really good for the atan2() function.
		/// atan() is used for the computeAngle() becuase its friendlier to use for 
		/// computing the angle of the motor.
		/// _________________________________________________________________________
		double a = atan2(Y, X);
		if (Theta != 0) {
			magnitude = FORWARD;			// May want this to be the REVERSE, but leave for now
		}
		else {
			if (X >= 0) {
				magnitude = pow(pow(X*cos(a), 2.0) + pow(Y*sin(a), 2.0), 0.5);// sqrt( x^2 + y^2 )
																		   // Need to correct so its not below 0 or above 255 since it will overflow. 256 = 1
				magnitude = map(magnitude, 0, coordinatePos, NEUTRAL, FORWARD);
				if (magnitude > FORWARD) {
					magnitude = FORWARD;
				}
				else if (magnitude < NEUTRAL) {
					magnitude = NEUTRAL;
				}
			}
			else if (X < 0) {
				magnitude = pow(pow(X*cos(a), 2.0) + pow(Y*sin(a), 2.0), 0.5);// sqrt( x^2 + y^2 )
																				// Need to correct so its not below 0 or above 255 since it will overflow. 256 = 1
				magnitude = map(magnitude, 0, coordinateNeg, NEUTRAL, REVERSE);
				if (magnitude > NEUTRAL) {
					magnitude = NEUTRAL;
				}
				else if (magnitude < REVERSE) {
					magnitude = REVERSE;
				}
			}
		}
	}

	void computeAngle(void) {
		/// _________________________________________________________________________
		/// This is just simply finding what the angle is from x and y.  Need to 
		/// shift the origin from (127,127) to (0,0) to get a good angle. The atan2()
		/// function gives undesirable results so using atan().
		/// This will give a value between -90 and 90.  So if in reverse it needs to 
		/// be tracked.  Should be accounted for in the magnitude.  
		/// _________________________________________________________________________
		if (Theta > 0) {
			angle = ANGLEMAX;
		}
		else if (Theta < 0) {
			angle = -ANGLEMAX;
		}
		else {
			angle = atan(Y / X);
		}
		if (angle > ANGLETHRESH && X < 0) {
			angle = -ANGLEMAX;
		}
		else if (angle < -ANGLETHRESH && X < 0) {
			angle = ANGLEMAX;
		}
	}

	void ignoreTheta(void) {
		/// _________________________________________________________________________
		/// This function is just for when no theta pin is used.  It eliminates the 
		/// noise that the pin will be experiencing from nothing plugged into it
		/// _________________________________________________________________________
		Theta = 0;
	}
	bool lowerMotor(void) {
		/// _________________________________________________________________________
		/// This function is used for the Trim down feature of the PADS. When pushing
		/// in the reverse direction it should lower the motor, but will need to be 
		/// in the trimming mode of the controls
		/// _________________________________________________________________________
		if (X > 0) {
			return true;
		}
		else {
			return false;
		}
	}
	bool raiseMotor(void) {
		/// _________________________________________________________________________
		/// This function is used for the Trim up feature of the PADS. When pushing
		/// in the forward direction it should lower the motor, but will need to be 
		/// in the trimming mode of the controls
		/// _________________________________________________________________________
		if (X < 0) {
			return true;
		}
		else {
			return false;
		}
	}

	bool compareX(void) {
		bool flag = true;
		if (oldX == X) {
			flag = false;
		}
		return flag;
	}
	bool compareY(void) {
		bool flag = true;
		if (oldY == Y) {
			flag = false;
		}
		return flag;
	}
	bool compareTheta(void) {
		bool flag = true;
		if (oldTheta == Theta) {
			flag = false;
		}
		return flag;
	}

	void printValues(void) {
		Serial.print("x: ");
		Serial.print(X);
		Serial.print(" y: ");
		Serial.print(Y);
		Serial.print(" Theta: ");
		Serial.println(Theta);
	}

	int getMagnitude(void) {
		return magnitude;
	}
	int getAngle(void) {
		return angle*radtoDeg;
	}
	void setMagnitude(int a) {
		magnitude = a;
	}
	int setAngle(int a) {
		angle = a;
	}
	int getX(void) {
		return X;
	}
	int getY(void) {
		return Y;
	}
	int getTheta(void) {
		return Theta;
	}
	int getOldX(void) {
		return oldX;
	}
	int getOldY(void) {
		return oldY;
	}
	int getOldTheta(void) {
		return oldTheta;
	}
	void setOldX(int val) {
		oldX = val;
	}
	void setOldY(int val) {
		oldY = val;
	}
	void setOldTheta(int val) {
		oldTheta = val;
	}
};