#include "joystick.h"
joystick3 jStick(1,2,3);
int t1, t2;
#define deltaT_Thresh 100

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* TODO: When theta pin is connected get ride of ignoreTheta() in readJoystick function. */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#define thrustPin 9
#define switchPin 8

String inString = "";
void setup() {
  Serial.begin(9600);
  Serial.print("Joystick Test");
  pinMode(switchPin, OUTPUT);
  digitalWrite(switchPin,HIGH);
  t1 = millis();
  t2 = millis();
}

void loop() {
//  jStick.RawInformation();
//  if(Serial.available()){
//    inString = Serial.readString();
//    if(inString == "on" || inString == "ON" || inString == "On"){
//      digitalWrite(switchPin, LOW);
//      Serial.println("ON");
//    }
//    else {
//      digitalWrite(switchPin, HIGH);
//      Serial.println("Closed");
//    }
//  }
  t2 = millis();
  if( abs(t2 - t1) > deltaT_Thresh){
    jStick.readJoystick();
//    jStick.printValues();
    Serial.print(" Magnitude: ");
    Serial.print(jStick.getMagnitude());
    Serial.print("  Angle: ");
    Serial.println(jStick.getAngle());
    t1 = millis();
    analogWrite(thrustPin,jStick.getMagnitude());
  }
}
