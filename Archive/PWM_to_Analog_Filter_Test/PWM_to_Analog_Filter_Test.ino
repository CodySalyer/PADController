#define pwmPin 9
int desiredPos = 0;
String mos;

int conversion(char* str,int& sign);
void typeMotorSpeed( void );

void setup() {
  pinMode(pwmPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  typeMotorSpeed();
  analogWrite(pwmPin,desiredPos);
}






/* Don't Change this! */
int conversion(char* str,int& sign){
  if(str == '-'){
    sign = -1;
    return 0;
  }
  if((str >= '0') && (str <= '9')){
    return (str - '0');
  }
}

/* Don't Change this! */
void typeMotorSpeed( void ){
  if(Serial.available() > 0){
    int sign = 1;
    desiredPos = 0;
    mos = Serial.readString();
    for(int i = 0; i < mos.length(); ++i){
      desiredPos += pow(10,(mos.length() - i -1))*conversion(mos[i],sign);
    }
    desiredPos *= sign;
    Serial.println(desiredPos);
  }
}
