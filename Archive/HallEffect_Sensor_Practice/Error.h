#pragma once
int micros() {
	return 1;
}
int millis() {
	return 3;
}

class Error {
	/// ***************************************************************
	/// Auther: Aaron Sonderegger
	/// Date: Novemeber 2017
	/// ***************************************************************

	/// _________________________________________________________________________
	/// This function takes the error from the feedback loop and converts it to a 
	/// PID controller.  
	/// _________________________________________________________________________
private:
	int Err;
	bool sign = false;
	int t = 0;
	int oldError = 0;
	int intError = 0;
	int dt = 0;
	int U = 0;

	/// Controller Gains
	// TODO: Tune Kp, Kd, Ki.  As of now the controller works as just a Proportional controller
	// with Kp = 12.  Works pretty well.  Only downfall I've run into is when the motor has to 
	// sweep 180 [degrees].  It gets going really fast.  Thats where Kd is needed.  Not to sure
	// if the Ki is really needed.  
	// fix the input U, as of now the one direction of rotaion works great with damping the 
	// other direction is like it switches back and forth between where it needs to go
	double Kr = 118.0 / 90.0;		// Converts degree to the number of steps in system
	const int Kp = 15;				// Proportional controller gain
	const int Kd = 0;				// Derivative controller gain
	const int Ki = 0;				// integrator controller gain
					// TODO: Right now there is a problem with this in one direction.  I think it's 
					// because I'm changing the sign of Err.  
public:
	Error() {
		Err = 0;
		sign = true;
	}
	void takeErrorReading(int desired, int actual) {
		/// _________________________________________________________________________
		/// This function will take the joystick angle and the actual angle and 
		/// compare them with one another to determine the input to the steering 
		/// motor.
		/// _________________________________________________________________________
		oldError = Err;
		dt = (millis() - t) / 1000;			// [s], time change since last reading 
		Err = Kr*desired - actual;			// [steps], this is the difference in steps
		U = Kp*Err +Ki*(oldError + Err)*dt + Kd*(Err - oldError) / dt; // PID controller input


		if (Err < 0) {
			Err = -1 * Err;
		}
		// This will determine the direction of the motor.  
		if (U < 0) {	
			sign = true;
			U *= -1;			
		}
		else {
			sign = false;
		}
		t = micros();
	}
	bool getSign(void) {
		return sign;
	}
	int getError(void) {
		return Err;
	}
	int getInput(void) {
		return U;
	}
};