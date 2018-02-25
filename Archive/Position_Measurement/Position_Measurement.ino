#include "hallEncoder120.h"

#define OUTSIDE_PIN 24
#define INSIDE_PIN 25

#define aPin 8
#define bPin 9
#define cPin 10

Aarons_Encoder sMotor(aPin, bPin, cPin);
 

void setup() {
  Serial.begin(9600);
  Serial.println("Positon Test");
  Serial.println("Turn motor to hit the switch on the edge");
  pinMode(OUTSIDE_PIN, INPUT);
  pinMode(INSIDE_PIN, INPUT);
//  attachInterrupt(0, setZeroPosition, CHANGE);
//  attachInterrupt(1, outputFinalValue, CHANGE);
}

void loop() {
  if(digitalRead(OUTSIDE_PIN) == HIGH){
    Serial.print("What I think is zero: ");
    Serial.print(sMotor.getPosition());
    Serial.println("    Position set to 0");
    sMotor.setPosition(0);
  }
  if( digitalRead(INSIDE_PIN) == HIGH){
    Serial.print("Position: ");
    Serial.println(sMotor.getPosition());
  }
  sMotor.readPinsD();
  sMotor.trackPositionS();
}

