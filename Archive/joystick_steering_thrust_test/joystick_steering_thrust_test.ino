#include "hallEncoder120.h"
#include "Error.h"
#include "brushlessControl.h"
#include "joystick.h"

/* Analog Pins */
#define xPin 1
#define yPin 2
#define thetaPin 3
/* Digital Pins */
#define switchPin1 25  // Purple/ inner switch
#define switchPin2 23  // Grey/ outer switch
#define dirPin 2
#define enaPin 4
#define speedPin 7
#define brakePin 3
#define HALLA 8
#define HALLB 9
#define HALLC 10
#define thrustPin 6
#define etechOn 5
#define interface 54

Error e;
Aarons_Encoder sM(HALLA, HALLB, HALLC);
brushlessControl BLM(enaPin, brakePin, dirPin, speedPin);
joystick3 joyStick(xPin, yPin, thetaPin);

int limits = 10;
int startUpSpeed = 65;

int t1, t2;
bool doStuff = false;
String inString = "";
/* TODO: set a value for how often the joystick should be run */
#define deltaT_Thresh 10
/* TODO: set a value for what the position error should be */
#define errorThresh 4
/* TODO: set a value for what the proportional gain should be */

void driveMotor(void);
void findMyPosition(void);

void setup() {
  pinMode(etechOn, OUTPUT);
  digitalWrite(etechOn,HIGH);
  Serial.begin(9600);
 // Serial.println("Steering Joystick Test");
  pinMode(switchPin1,INPUT);
  pinMode(switchPin2,INPUT);
  pinMode(interface, OUTPUT);
//  attachInterrupt(0, limitSwitch1Hit, CHANGE);
//  attachInterrupt(1, limitSwitch2Hit, CHANGE);
//  while(limits > 2){
//    Serial.println("finding Position");
//    findMyPosition();
//  }
  t1 = millis();
  t2 = millis();
  e.takeErrorReading(0,sM.getPosition());
}


void loop() {
  turnEtechOn();
  sM.readPinsD();
  sM.trackPositionS();
  e.takeErrorReading(joyStick.getAngle(), sM.getPosition());
  if(doStuff){
    t2 = millis();
    if( t2 - t1 > deltaT_Thresh){
      joyStick.readJoystick();
      t1 = millis();
    }
  }
  driveMotor();
//  joyStick.RawInformation();
//  Serial.print("mag: ");
//  Serial.print(joyStick.getMagnitude());
//  Serial.print(" angle: ");
//  Serial.print(joyStick.getAngle());
//  Serial.print(" X: ");
//  Serial.print(joyStick.getX());
//  Serial.print(" Y: ");
//  Serial.println(joyStick.getY());
//  Serial.print(" angle: ");
//  if(e.getSign()){
//    Serial.print("-");
//  }
//  Serial.println(joyStick.get());
}

void driveMotor(void){
    BLM.setDirection(e.getSign());
    if(e.getError() < errorThresh){
      BLM.setMotorSpeed(0);
      analogWrite(thrustPin,joyStick.getMagnitude());
    }
    else{
      BLM.setMotorSpeed(e.getInput());
    }
    BLM.runMotor();
}

void findMyPosition(void){
  int t_2;
  int t__ = 50;
  BLM.setDirection(false);
  BLM.setMotorSpeed(startUpSpeed);
  while(!digitalRead(switchPin1)){
    BLM.runMotor();
    sM.readPinsD();
    sM.trackPositionS();
    Serial.println(digitalRead(2));
    if( digitalRead(switchPin1) ){
      Serial.println("First button Pushed");
      BLM.stopMotor();
      sM.setPosition(120);
      limits = sM.getPosition();
      break;
    }
  }
  Serial.println("switch2");
  BLM.setDirection(true);
  while(1){
    BLM.runMotor();
    sM.readPinsD();
    sM.trackPositionS();
    Serial.println(digitalRead(2));
    if( digitalRead(switchPin2) ){
      t_2 = millis();
      Serial.println("Second button Pushed");
      BLM.stopMotor();
      limits += sM.getPosition();
      break;
    }
  }
}

void turnEtechOn(void){
  if(Serial.available()){
    inString = Serial.readString();
    if(inString == "on" || inString == "ON" || inString == "On"){
      digitalWrite(etechOn, LOW);
      Serial.println("ON");
      doStuff = true;
      digitalWrite(interface,HIGH);
    }
    else {
      digitalWrite(etechOn, HIGH);
      Serial.println("Closed");
      joyStick.setMagnitude(127);
      joyStick.setAngle(0);
      doStuff = false;
      digitalWrite(interface, LOW);
    }
  }
}

//void limitSwitch1Hit(void){
//  /* TODO: set the direction corresponding to the correct switch*/
//  /* TODO: adjust this to slowly go back and forth to get the position correct */
//  BLM.stopMotor();
//  BLM.setDirection(false);
//  BLM.setMotorSpeed(limitSwitchSpeed);
//  sM.setPosition(one80);
//}
//
//void limitSwitch2Hit(void){
//  /* TODO: set the direction corresponding to the correct switch*/
//  /* TODO: adjust this to slowly go back and forth to get the position correct */
//  BLM.stopMotor();
//  BLM.setDirection(true);
//  BLM.setMotorSpeed(limitSwitchSpeed);
//  sM.setPosition(-one80);
//}

