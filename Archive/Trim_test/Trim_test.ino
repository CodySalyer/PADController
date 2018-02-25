#include "joystick.h"
#include "relayBoard.h"
#include "aaronsButton.h"

/* Trim Testing */
#define trimup 11
#define trimdown 12
//#define trimButton 1
#define randomEtech 6
#define xPin 0
#define yPin 1
#define thetaPin 2
#define trimmedUpButton 22

joystick3 joy(xPin, yPin, thetaPin);
relayBoard actuator(randomEtech, trimup, trimdown);
//aaronsButton joyButton(trimButton);

String inString = "";

void setup() {
  Serial.begin(9600);
  Serial.println("Trim Motor Test");
  pinMode(7,INPUT);
}

void loop() {
  /* Control with Serial Port and typing "up" or "down" */
  //joyButton.readButton_();
//  if(Serial.available()){
//    inString = Serial.readString();
//    actuator.runActuator(inString);
//  }
  /* Control the trim button and joystick */
  //if( joyButton.getState() == 3 ){
    joy.readJoystick();
    if( joy.lowerMotor() ){
      actuator.runActuator("down");
      Serial.print(joy.getX());
    }
    else if( joy.raiseMotor() && !digitalRead(trimmedUpButton) ){
      actuator.runActuator("up");
      Serial.println(joy.getY());
    }
    else{
      actuator.runActuator("Nothing");
    }
  
//  else{
//    digitalWrite(12,LOW);
//    actuator.runActuator(inString);
//  }
}


