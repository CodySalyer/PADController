class Aarons_EncoderV2 {
  /* Using an encoder that has 3 hall effect sensors and that are read
  4 times per revolution.  24 readings/360 degrees*/
private:
#define A 'a'
#define B 'b'
#define AB 'c'

  int PIN_A = 13;
  int PIN_B = 12;
  bool flagA = false;
  bool flagB = false;
  long pos = 0;
  int thresh = 2;
  char sensorOn;
  char oldSensorOn;
public:
  /* Defaults to PIN_A = 13, PIN_B = 12, PIN_C = 11.
  This constructor assigns pins to where user would like them to be on*/
  Aarons_EncoderV2(int pin_A, int pin_B) :
    PIN_A(pin_A),
    PIN_B(pin_B)
  {
    pinMode(pin_A, INPUT);
    pinMode(pin_B, INPUT);
  }

  /* This function reads using the digital Read function.  This takes about 16 microsencds to read 3 pins*/
  void readPinsD(void) {
    flagA = digitalRead(PIN_A);
    flagB = digitalRead(PIN_B);
    oldSensorOn = sensorOn;
    if (flagA && !flagB) {
      sensorOn = A;
    }
    else if (!flagA && flagB) {
      sensorOn = B;
    }
    else if (flagA && flagB) {
      sensorOn = AB;
    }
  }

  /* This function will follow what direction the pin is traveling and counts the amount of steps it will take*/
  int trackPositionS(void) {
    /*+: A -> AB -> B -> BC -> C -> CA
    -: CA -> C -> BC -> B -> AB -> A*/
    switch (sensorOn) {
    case A:
      switch (oldSensorOn) {
      case AB:
        --pos;
        break;
      case B:
        ++pos;
        break;
      default:
        break;
      }
      break;
    case B:
      switch (oldSensorOn) {
      case AB:
        ++pos;
        break;
      case A:
        --pos;
        break;
      default:
        break;
      }
      break;
    case AB:
      switch (oldSensorOn) {
      case A:
        ++pos;
        break;
      case B:
        --pos;
        break;
      default:
        break;
      }
      break;
    }
  }

  /* This function returns the position of the pin that it's sitting at*/
  int getPosition(void) {
    return pos;
  }

  /* This function allows me to change the position of the Pin, If hit like a limit switch, changes to desired value*/
  int setPosition(int newPosition) {
    pos = newPosition;
  }

  /* This function prints out what pin is currently on*/
  void highPin() {
    Serial.println(sensorOn);
  }

};
