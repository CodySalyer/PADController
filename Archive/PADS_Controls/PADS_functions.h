#pragma once
  /// ***************************************************************
  /// Auther: Aaron Sonderegger
  /// Date: Novemeber 2017
  /// ***************************************************************
#define startUpSpeed 135
#define errorThresh 4



void findMyPosition(void){
  int t_2;
  int t__ = 50;
  BLM.setDirection(false);
  BLM.setMotorSpeed(startUpSpeed);
  while(!digitalRead(OUTSIDE_LIMIT_SWITCH_PIN)){
    sM.readPinsD();
    sM.trackPositionS();
    BLM.runMotor();
    if( digitalRead(OUTSIDE_LIMIT_SWITCH_PIN) ){
      BLM.stopMotor();
      sM.setPosition(118);
      fmp_error_limit = sM.getPosition();
      break;
    }
  }
  BLM.setDirection(true);
  while( !digitalRead(INSIDE_LIMIT_SWITCH_PIN) ){
    BLM.runMotor();
    sM.readPinsD();
    sM.trackPositionS();
    if( digitalRead(INSIDE_LIMIT_SWITCH_PIN) ){
      t_2 = millis();
      BLM.stopMotor();
      fmp_error_limit += sM.getPosition();
      break;
    }
  }
}

void driveSteeringMotor(void){
    BLM.setDirection( e.getSign() );
    if(e.getError() < errorThresh){
      BLM.setMotorSpeed(0);
      analogWrite(THRUST_PIN,joyStick.getMagnitude());
    }
    else{
      BLM.setMotorSpeed(e.getInput());
    }
    BLM.runMotor();
}

void driveETECHMotor(void){
  analogWrite( THRUST_PIN, joyStick.getMagnitude() );
}

void driveActuator(void){
  if(joyStick.lowerMotor() /*&& !digitalRead(TRIMMED_DOWN_BUTTON_PIN)*/ ){
    rB.runActuator("down");
  }
  else if( joyStick.raiseMotor() && !digitalRead(TRIMMED_UP_BUTTON_PIN) ){
    rB.runActuator("up");
  }
  else{
    rB.runActuator("doNothing");
  }
}

void resetPosition(void){
  if(digitalRead(OUTSIDE_LIMIT_SWITCH_PIN) && sM.getPosition() != 118){
    sM.setPosition(118);
  }
  if(digitalRead(INSIDE_LIMIT_SWITCH_PIN) && sM.getPosition() != -118){
    sM.setPosition(-118);
  }
}

