#include "hallEncoder120.h"
#include "brushlessControl.h"
#include "Error.h"
#define HALLA 8    // A is Gray wire
#define HALLB 9    // B is Green wire
#define HALLC 10    // C is White wire
Aarons_Encoder steer(HALLA, HALLB, HALLC);

#define DirectionPin 2
#define BrakePin 3
#define EnablePin 4
#define potPin 7
brushlessControl BLMotor(EnablePin, BrakePin, DirectionPin, potPin);

Error posError;

String inString;
int desiredPos = 0;
//const double Kr = 1;//120.0/180.0;



void setup() {
  Serial.begin(9600);
  Serial.println("Encoder Test");
}

/* Functions used: Defined below. Don't Change this! */

void typeMotorSpeed( void );
void DriveMotor( void );

void loop() {
  typeMotorSpeed();
  steer.readPinsD();
  steer.trackPositionS();
  posError.takeErrorReading(desiredPos, steer.getPosition());
  DriveMotor();
}





/* Don't Change This! */
void DriveMotor(void){
  BLMotor.setDirection(posError.getSign());
  if(posError.getError() < 3){
    BLMotor.setMotorSpeed(0);
  }
  else{
    BLMotor.setMotorSpeed(posError.getInput());
  }
  BLMotor.runMotor();
}

/* Don't Change this! */
void typeMotorSpeed( void ){
  if(Serial.available()){
    inString = Serial.readString();
    desiredPos = inString.toInt();
    desiredPos = desiredPos;
    Serial.print("Value: ");
    Serial.println(desiredPos);
    inString = "";
  }
}
