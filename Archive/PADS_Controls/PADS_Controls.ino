  /// ***************************************************************
  /// Auther: Aaron Sonderegger
  /// Date: December 2017
  /// ***************************************************************

/// _________________________________________________________________________
/// Include the different Headers that are needed for the controls to work
/// _________________________________________________________________________
#include "Error.h"
#include "aaronsButton.h"
#include "brushlessControl.h"
#include "hallEncoder120.h"
#include "joystick.h"
#include "relayBoard.h"

/// _________________________________________________________________________
/// Define the pins used in the different classes
/// _________________________________________________________________________
#define X_PIN 1                 // A
#define Y_PIN 2                 // A
#define THETA_PIN 3             // A
joystick3 joyStick(X_PIN, Y_PIN, THETA_PIN);

#define DIR_PIN 2               // D
#define BRAKE_PIN 3             // D, Yellow
#define ENABLE_PIN 4            // D, Orange
#define SPEED_PIN 7             // PWM
brushlessControl BLM(ENABLE_PIN, BRAKE_PIN, DIR_PIN, SPEED_PIN);

#define THRUST_PIN 6            // Needs to be a PWM pin

#define PIN_A 8                 // D, Hall Grey
#define PIN_B 9                 // D, Hall Green
#define PIN_C 10                 // D, Hall White
Aarons_Encoder sM(PIN_A, PIN_B, PIN_C);

#define TRIM_UP_PIN 11          // D
#define TRIM_DOWN_PIN 12         // D
#define ETECH_ON_PIN 5          // D
relayBoard rB(ETECH_ON_PIN, TRIM_UP_PIN, TRIM_DOWN_PIN);

#define JOYSTICK_BUTTON_PIN 26  // D ************ TODO: Attach Pin
aaronsButton buttonOnJoy( JOYSTICK_BUTTON_PIN );
/// _________________________________________________________________________
/// Define different pins that will be used
/// _________________________________________________________________________
#define OUTSIDE_LIMIT_SWITCH_PIN 24    // D
#define INSIDE_LIMIT_SWITCH_PIN 25     // D
#define TRIMMED_UP_BUTTON_PIN 22       // D
//#define TRIMMED_DOWN_BUTTON_PIN 23     // D


//#define TRIM_STATE_LED 52             // ********** TODO: Attach Pin
//#define DRIVING_STATE_LED 53          // ********** TODO: Attach Pin
//#define PARKING_STATE_LED 54          // ********** TODO: Attach Pin


// TODO: Adjust limit switches so there isn't the noise on them.

int fmp_error_limit = 10;
bool posFound = false;
Error e;

/// _________________________________________________________________________
/// Include a bunch of functions that are written outside of the different 
/// classes created.
/// _________________________________________________________________________
#include "PADS_functions.h"


/// =========================================================================
void setup() {
  Serial.begin(9600);
}

/// =========================================================================

void loop() {
  buttonOnJoy.readButton_();
  sM.readPinsD();
  sM.trackPositionS();
  switch( buttonOnJoy.getState() ){
    case 0:
      /// _________________________________________________________________________
      /// This is the Off state
      /// _________________________________________________________________________
//      digitalWrite(TRIM_STATE_LED, LOW);
//      digitalWrite(DRIVING_STATE_LED, LOW);
//      digitalWrite(PARKING_STATE_LED, LOW);
      rB.turnEtechOFF();
      rB.runActuator("donothing");
      posFound = false;
      e.takeErrorReading(joyStick.getAngle(), sM.getPosition());
      Serial.println("Off");
      break;
    case 1:
      /// _________________________________________________________________________
      /// This is the Trim state
      /// _________________________________________________________________________
//      digitalWrite(TRIM_STATE_LED, HIGH);
//      digitalWrite(DRIVING_STATE_LED, LOW);
//      digitalWrite(PARKING_STATE_LED, LOW);
      joyStick.readJoystick();
      joyStick.setAngle(0);
      driveActuator();                // PADS_functions.h
      Serial.println("Trim");
      break;
    case 2:
      /// _________________________________________________________________________
      /// This is the driving state
      /// _________________________________________________________________________
//      digitalWrite(TRIM_STATE_LED, LOW);
//      digitalWrite(DRIVING_STATE_LED, HIGH);
//      digitalWrite(PARKING_STATE_LED, LOW);
      while( fmp_error_limit > 2 && posFound){
        Serial.print("finding");
        findMyPosition();                   // PADS_functions.h
      }
      e.takeErrorReading(joyStick.getAngle(), sM.getPosition());
      posFound = true;
      rB.runActuator("donothing");
      //rB.turnEtechON();
      joyStick.readJoystick();
      driveETECHMotor();              // PADS_functions.h
      resetPosition();                // PADS_functions.h
      Serial.println("Drive");
      break;
    case 3:
      /// _________________________________________________________________________
      /// This is the parking state
      /// _________________________________________________________________________
//      digitalWrite(TRIM_STATE_LED, LOW);
//      digitalWrite(DRIVING_STATE_LED, LOW);
//      digitalWrite(PARKING_STATE_LED, HIGH);
      joyStick.readJoystick();
      e.takeErrorReading(-joyStick.getAngle(), sM.getPosition());
      rB.runActuator("donothing");
      resetPosition();                // PADS_functions.h
      Serial.println("Park");
      break;
    default:
//      digitalWrite(TRIM_STATE_LED, HIGH);
//      digitalWrite(DRIVING_STATE_LED, HIGH);
//      digitalWrite(PARKING_STATE_LED, HIGH);
      /// Debuging, change button max to 4 for this 
//      Serial.print("Pin 7: ");
//      Serial.print( digitalRead(7) );
//      Serial.print(" Pin 8: ");
//      Serial.print( digitalRead(8) );
//      Serial.print(" pin 9: ");
//      Serial.print(digitalRead(9));
//      Serial.print(" Pin 10: ");
//      Serial.println(digitalRead(10));
      break;
  }
  driveSteeringMotor();           // PADS_functions.h
  BLM.runMotor();
}
