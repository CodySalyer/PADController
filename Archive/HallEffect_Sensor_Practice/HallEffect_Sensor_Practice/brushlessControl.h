class brushlessControl {
private:
#define CW true
#define CCW false
#define BRAKE true
#define NO_BRAKE false
#define ENABLE false
#define NOT_ENABLE true
  int enablePin = 7;
  int brakePin = 13;
  int directionPin = 8;
  int speedPin = 9;
  bool dir;
  int motorSpeed = 0;
public:
  brushlessControl(int _enablePin, int _brakePin, int _directionPin, int _speedPin) :
    enablePin(_enablePin),
    brakePin(_brakePin),
    directionPin(_directionPin),
    speedPin(_speedPin){
    pinMode(directionPin, OUTPUT);
    pinMode(brakePin, OUTPUT);
    pinMode(enablePin, OUTPUT);
    pinMode(speedPin, OUTPUT);
  }
  void runMotor(void) {
    digitalWrite(directionPin, dir);
    digitalWrite(enablePin, ENABLE);
    digitalWrite(brakePin, NO_BRAKE);
    analogWrite(speedPin, motorSpeed);
  }

  void setMotorSpeed(int _speed) {
    if (_speed > 255) {
      motorSpeed = 255;
    }
    else {
      motorSpeed = _speed;
    }
  }
  void coastMotor(void) {
    digitalWrite(enablePin, NOT_ENABLE);
  }
  void stopMotor(void) {
    digitalWrite(enablePin, NOT_ENABLE);
    digitalWrite(brakePin, BRAKE);
  }

  void setDirection(bool val) {
    dir = val;
  }

  bool getDirection(void) {
    return dir;
  }
  int getSpeed(void) {
    return motorSpeed;
  }
};
