#include "hallEncoder120.h"
#include "brushlessControl.h"

/* Digital Pins */
#define switchPin1 2
#define switchPin2 3
#define dirPin 4
#define enaPin 11
#define speedPin 6
#define brakePin 7
#define HALLA 8
#define HALLB 9
#define HALLC 10

#define startUpSpeed 60


Aarons_Encoder sM(HALLA, HALLB, HALLC);
brushlessControl BLM(enaPin, brakePin, dirPin, speedPin);

void goCCW(void);
void goCW(void);

void setup() {
  Serial.begin(9600);
  Serial.println("Test on the Limit Switch Start Up");
  pinMode(switchPin1, INPUT);
  pinMode(switchPin2, INPUT);
//  attachInterrupt(0, limitSwitch1Hit, HIGH);
//  attachInterrupt(1, limitSwitch2Hit, HIGH);
  goCW();
}

void loop() {
  goCW();
  goCCW();
}
void goCW(void){
  BLM.setDirection(false);
  BLM.setMotorSpeed(startUpSpeed);
  while(!digitalRead(switchPin1)){
    BLM.runMotor();
    sM.readPinsD();
    sM.trackPositionS();
    if(digitalRead(switchPin1)){
      Serial.println(sM.getPosition());
      BLM.stopMotor();
      sM.setPosition(120);
      delay(1000);
      break;
    }
  }
}
void goCCW(void){
  BLM.setDirection(true);
  BLM.setMotorSpeed(startUpSpeed);
  while(!digitalRead(switchPin2)){
    BLM.runMotor();
    sM.readPinsD();
    sM.trackPositionS();
    if(digitalRead(switchPin2)){
      Serial.println(sM.getPosition());
      BLM.stopMotor();
      sM.setPosition(-120);
      delay(1000);
      break;
    }
  }
}
//
//void limitSwitch1Hit(void){
//  /* TODO: set the direction corresponding to the correct switch*/
//  /* TODO: adjust this to slowly go back and forth to get the position correct */
//  BLM.stopMotor();
//  BLM.setDirection(true);
//  BLM.setMotorSpeed(startUpSpeed);
//  sM.setPosition(120);
//  BLM.runMotor();
//  Serial.println("You hit the Positive switch");
//}
//
//void limitSwitch2Hit(void){
//  /* TODO: set the direction corresponding to the correct switch*/
//  /* TODO: adjust this to slowly go back and forth to get the position correct */
//  BLM.stopMotor();
//  BLM.setDirection(false);
//  BLM.setMotorSpeed(startUpSpeed);
//  sM.setPosition(-120);
//  BLM.runMotor();
//  Serial.println("You hit the Negative switch");
//}
