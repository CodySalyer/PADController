#include <AccelStepper.h>

AccelStepper stepper(1,3,2);

void setup(){
  Serial.begin(9600);
  stepper.setMaxSpeed(100);
  stepper.setAcceleration(20);
  stepper.moveTo(500);
}

void loop(){
  Serial.write("Hello Computer");
  if (stepper.distanceToGo() == 0){
    stepper.moveTo( -stepper.currentPosition() );
  }
  stepper.run();
}

