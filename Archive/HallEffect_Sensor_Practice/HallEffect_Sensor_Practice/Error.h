#pragma once
class Error {
private:
  int Err;
  bool sign = false;
public:
  void takeErrorReading(int* desired, int* actual) {
    Err = desired - actual;
    if (Err < 0) {
      sign = false;
      Err = -1 * Err;
    }
    else {
      sign = true;
    }
  }
  bool getSign(void) {
    return sign;
  }
  int getError(void) {
    return Err;
  }
};
