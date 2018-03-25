#include <LiquidCrystal.h>
#include <string.h>

// define connections for lcd screen
const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;

// create lcd display object
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup()
{
	// Starts the LCD display
	lcd.begin(16, 2);
	lcd.print("hello, world!");

	// Start serial port to communicate with Serial port
	Serial.begin(9600);
}

void loop() 
{
	// when characters arrive over the serial port...
	if (Serial.available()) 
	{
		// wait a bit for the entire message to arrive
		delay(100);

		// clear the screen
		lcd.clear();

		// read all the available characters
		while (Serial.available() > 0) 
		{
      char i = Serial.read();
      if(i == 'a')
      {
        Serial.write("controller");
      }
			lcd.write(i);
		}
	}
}
