#include <SoftwareSerial.h>
#include "joystick.h"

#define RX 2
#define TX_X 3
#define TX_Y 4
#define TX_Theta 5
SoftwareSerial unox(RX,TX_X);         // RX, TX
SoftwareSerial unoy(RX,TX_Y);         // RX, Tx
SoftwareSerial unotheta(RX,TX_Theta); // RX, TX

#define xPin A0
#define yPin A1
#define thetaPin A2

joystick3 joystick(xPin, yPin, thetaPin);

void setup() {
  Serial.begin(9600);
  Serial.println("I'm the UNO and I'm the Master");
  unox.begin(4800);
  unoy.begin(4800);
  unotheta.begin(9600);
}

void loop() {
  Serial.println(analogRead(xPin));
  joystick.readJoystick();
  Serial.print("x: ");
//  Serial.print(analogRead(xPin));
  Serial.print(joystick.getX());
  Serial.print(" y: ");
//    Serial.print(analogRead(yPin));
  Serial.print(joystick.getY());
  Serial.print(" theta: ");
//    Serial.println(analogRead(thetaPin));
  Serial.print(joystick.getTheta());
  Serial.print(" magnitude: ");
  Serial.print(joystick.getMagnitude());
  Serial.print(" Angle: ");
  Serial.print(joystick.getAngle());
  int t1 = micros();
    unox.write(joystick.getX());
    unoy.write(joystick.getY());
    unotheta.write(joystick.getTheta());
  int t2 = micros();
  Serial.print(" Time: ");
  Serial.println(t2 - t1);
  joystick.setOldX(joystick.getX());
  joystick.setOldY(joystick.getY());
  joystick.setOldTheta(joystick.getTheta());
}
