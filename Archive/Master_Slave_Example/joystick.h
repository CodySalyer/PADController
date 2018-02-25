class joystick3 {
private:
#define xThresh 50
#define x0 525
#define xMax 989
#define xMin 9
#define yThresh 50
#define y0 511
#define yMax 994
#define yMin 30
#define thetaThresh 100
#define theta0 540
#define thetaMax 1023
#define thetaMin 0
#define FORWARD 255
#define NEUTRAL 127
#define REVERSE 0  
  int xPin = 0;
  int yPin = 1;
  int thetaPin = 2;

  int X = 0;
  int Y = 0;
  int Theta = 0;

  int oldX = 0;
  int oldY = 0;
  int oldTheta = 0;
public:
  joystick3(int _xPin, int _yPin, int _theta) :
    xPin(_xPin), yPin(_yPin), thetaPin(_theta) {
  }

  void readJoystick(void) {
    X = analogRead(xPin);
    if (abs(X - x0) < xThresh) {
      X = x0;
    }
    X = X >= x0 ? /* if Statement */
      map(X, x0, xMax, NEUTRAL, FORWARD) :  /* if True */
      map(X, x0, xMin, NEUTRAL, REVERSE);  /* if False */
    Y = analogRead(yPin);
    if (abs(Y - y0) < yThresh) {
      Y = y0;
    }
    Y = Y >= y0 ?                 // if Statement
      map(Y, y0, yMax, NEUTRAL, FORWARD) :          // if True
      map(Y, y0, yMin, NEUTRAL, REVERSE);          // if False
    Theta = analogRead(thetaPin);
    if (abs(Theta - theta0) < thetaThresh) {
      Theta = theta0;
    }
    Theta = Theta >= theta0 ?
      map(Theta, theta0, thetaMax, NEUTRAL, FORWARD) :
      map(Theta, theta0, thetaMin, NEUTRAL, REVERSE);
  }

  int getMagnitude(void) {
    if (Theta != NEUTRAL) {
      return FORWARD;
    }
    else {
      int magnitude = pow(pow(X, 2) + pow(Y, 2), 0.5);
      if(magnitude < REVERSE){
        magnitude = REVERSE;
      }
      else if(magnitude > FORWARD){
        magnitude = FORWARD;
      }
      return magnitude;
    }
  }
  int getAngle(void) {
    if (Theta > NEUTRAL) {
      return 180;
    }
    else if (Theta < NEUTRAL) {
      return -180;
    }
    else {
      return atan2(X-NEUTRAL, Y-NEUTRAL)*180/3.1415;
    }
  }

  bool compareX(void) {
    bool flag = true;
    if (oldX == X) {
      flag = false;
    }
    return flag;
  }
  bool compareY(void) {
    bool flag = true;
    if (oldY == Y) {
      flag = false;
    }
    return flag;
  }
  bool compareTheta(void){
    bool flag = true;
    if (oldTheta == Theta) {
      flag = false;
    }
    return flag;
  }

  int getX(void) {
    return X;
  }
  int getY(void) {
    return Y;
  }
  int getTheta(void) {
    return Theta;
  }
  int getOldX(void) {
    return oldX;
  }
  int getOldY(void) {
    return oldY;
  }
  int getOldTheta(void) {
    return oldTheta;
  }
  void setOldX(int val) {
    oldX = val;
  }
  void setOldY(int val) {
    oldY = val;
  }
  void setOldTheta(int val) {
    oldTheta = val;
  }
};
