// --------- Joystick Variables -------------------------------
#define xpin A1                 // Joystick x pin 
#define ypin A2                 // Joystick y pin

#define y_thresh 90             // How much the analog varies at center
#define x_thresh 90             // How much the analog varies at center
#define x0 355                  // Center analog read x variable
#define y0 365                  // Center analog read y variable
#define y_max 1000              // Max y analog read variable
#define y_min 2                 // Min y analog read variable
#define x_max 1000              // Max x analog read variable
#define x_min 22                // Min x analog read variable

int x_pos;                      // variable for x position
int y_pos;                      // variable for y position
int theta;                      // variable for angle 
int theta_old;

// --------- Motor Variables / Librarys -----------------------
#include <AccelStepper.h>
AccelStepper stepper(1,3,2);    // Ross: Motor type, pin 2, pin 3
#define full_rev 15400          // Number of counts for a full 360 degrees

// --------- Propulsion Motor Variables -----------------------
#include <Servo.h>
Servo pod;
int magnitude;
int state = 1;

// ========= Setup Loop =======================================
void setup() {
  Serial.begin(9600);           // For output on screen
  stepper.setMaxSpeed(2000);
  stepper.setSpeed(1000);
  stepper.setAcceleration(1000);
  pod.attach(7);
}


// ========= Main Loop ========================================
void loop() {
  if(state == 1){
    read_joystick();              // Function Defined Below
    joystick_angle();             // Function Defined Below
    print_values();               // Function Defined Below
    magnitude_of_joystick();
    drive_motor();
    if( analogRead(A3) > 700){
      state = 2;
    }
    theta_old = theta;
  }
  else{
    Serial.write("Program Stopped\n");
  }
}

// ========= Functions that are Called ========================
// --------- Stepper Motor ------------------------------------
void drive_motor(){
  int motor_pos = 0;
  motor_pos = theta >= 0 && theta < 180 ? map(theta, 0,180, 0,(full_rev/2)) : map(theta, 359,180, 0,-(full_rev/2));
  //Serial.print(motor_pos);
  /*
  // One option to test
  if(stepper.currentPosition() != 0){
    stepper.run();
    read_joystick();
  }
  */
  // Lines to measure stepper time.  
  //int to = millis();
  stepper.runToNewPosition(motor_pos);
  //Serial.print("time: ");
  //Serial.println(millis() - to);
  //delay(3000);
  int test_pod = 0;
  test_pod = map(magnitude, 0,100, 40,65);
  pod.write(test_pod);
}



/***************************************************************/
/***************************************************************/
/***************************************************************/

  /* TO DO: 
   *  1. Will Probably need to rotate my angle so 0 degrees 
   * to 90 degrees so that when push full y, I don't move motor.
   *  2. 
   */

/***************************************************************/
/***************************************************************/
/***************************************************************/

// --------- Angle from Joystick ------------------------------
void joystick_angle(){
  /* This function takes the x,y position from the joystick and 
  converts it to an angle for the motors to follow*/  
  theta = atan2(y_pos, x_pos)*180/3.1415;     // arctan(y/x) converts to degree
  if( theta < 0 ){
    theta = theta + 360;     // Output of atan2 is -180 to 180
  }
}



// --------- Magnitude Function -------------------------------
void magnitude_of_joystick(){
  magnitude = pow(x_pos*x_pos + y_pos*y_pos,0.5);   // This is power level of motors
}

// --------- Joystick Function --------------------------------
void read_joystick(){
  int xjoy = analogRead(xpin);  // Temp x Variable
  int yjoy = analogRead(ypin);  // Temp y Variable 
  if( abs(xjoy - x0) < x_thresh ){  // this if error in dead zone
    xjoy = x0;                      // sets joystick x to zero
  }
  if( abs(yjoy - y0) < y_thresh ){  // error in y dead zone
    yjoy = y0;                      // sets joystick y to zero
  }
  x_pos = xjoy >= x0 ? map(xjoy, x0,x_max, 0,100) : map(xjoy, x0,x_min, 0,-100);
  y_pos = yjoy >= y0 ? map(yjoy, y0,y_max, 0,-100) : map(yjoy, y0,y_min, 0,100);
}

// --------- Print the Values to Screen -----------------------
void print_values(){
//  Serial.write("x: ");
//  Serial.print(x_pos);
//  Serial.write(", y: ");
//  Serial.print(y_pos);
//  Serial.write(", theta: ");
//  Serial.write(", DEBUGING READING: "); // Trouble shooting message
//  Serial.println( analogRead(ypin) );   // Trouble shooting y readings
//  Serial.println( analogRead(xpin) );   // Trouble shooting x readings
//  Serial.print( analogRead(A3));
//  Serial.print("Stepper Position: ");
//  Serial.println(stepper.currentPosition());
//  Serial.print(theta);
//  Serial.write(", Mag: ");
//  Serial.println(magnitude);              
//  delay(1);
}
