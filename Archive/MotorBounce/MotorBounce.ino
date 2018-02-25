#include "Error.h"
#include "brushlessControl.h"
#include "hallEncoder120.h"

#define directionPin 4
#define enablePin 11
#define speedPin 6
#define brakePin 7
#define hallA 8
#define hallB 9
#define hallC 10

Error Err;
Aarons_Encoder encoder(hallA,hallB,hallC);
brushlessControl BLM(enablePin, brakePin, directionPin, speedPin);
int desiredPosition = 45;

void setup() {
  Serial.begin(9600);
  pinMode(2,INPUT);
  pinMode(3,INPUT);
  BLM.setMotorSpeed(65);
}

void loop() {
  encoder.readPinsD();
  encoder.trackPositionS();
  Err.takeErrorReading(desiredPosition, encoder.getPosition());
  if(Err.getError() < 3){
    BLM.stopMotor();
    BLM.setDirection( Err.getSign() );
    desiredPosition *= -1;
  }
  BLM.runMotor();
  Serial.print( digitalRead(2) );
  Serial.print( "    ");
  Serial.println( digitalRead(3) );
}
