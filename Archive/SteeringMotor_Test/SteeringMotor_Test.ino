#include "hallEncoder120.h"
#include "brushlessControl.h"
#include "Error.h"
#define HALLA 13    // A is Gray wire
#define HALLB 12    // B is Green wire
#define HALLC 11    // C is White wire
Aarons_Encoder steer(HALLA, HALLB, HALLC);

#define EnablePin 4
#define DirectionPin 3
#define BrakePin 2
#define potPin 9
brushlessControl BLMotor(EnablePin, BrakePin, DirectionPin, potPin);

Error posError;

String inString;
int desiredPos = 0;
int Kp = 10;


void setup() {
  Serial.begin(9600);
  Serial.println("Encoder Test");
}

/* Functions used: Defined below. Don't Change this! */
int conversion(char* str,int* sign);
void typeMotorSpeed( void );
void DriveMotor( void );

void loop() {
  //typeMotorSpeed();
  //steer.readPinsD();
  //steer.trackPositionS();
  //posError.takeErrorReading(desiredPos, steer.getPosition());
  //DriveMotor();
  //steer.printMessage("Position: ",steer.getPosition());
  //Serial.print(posError.getSign());
  //Serial.print(" ");
  //steer.printMessage("Error: ", posError.getSign());
  //steer.highPin();
  //steer.printMessage("Position: ",steer.getPosition());
  //steer.timeFunction("trackPositionS");
  //steer.timeFunction("trackPositionEI");
}


/* Test this! */
void DriveMotor(void){
  BLMotor.setDirection(posError.getSign());
  if(posError.getError() < 2){
    BLMotor.setMotorSpeed(0);
  }
  else{
    BLMotor.setMotorSpeed(Kp*posError.getError());
  }
  BLMotor.runMotor();
}

/* Don't Change this! */
void typeMotorSpeed( void ){
  if(Serial.available()){
    inString = Serial.readString();
    desiredPos = inString.toInt();
    Serial.print("Value: ");
    Serial.println(desiredPos);
    inString = "";
  }
}
