#pragma once
#include <math.h>

class Error 
{

private:
	int Error;
	bool sign;

public:

	/// constructor that takes the desired position and actual position
	void CalculateError(int desired, int actual)
	{
		Error = desired - actual;

		if (Error < 0)
		{
			sign = true;
		}

		else
		{
			sign = false;
		}
		Error = abs(Error);
	}

	/// returns if error is pos or negative true is negative
	bool getSign(void) 
	{
		return sign;
	}

	/// Returns the absolute value of the error
	int getError(void) 
	{
		return Error;
	}
};
