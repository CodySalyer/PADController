#define switch1Pin 2
#define switch2Pin 3
#define ledPin 13

bool ls1 = 0;
bool ls2 = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Limit Switch Test");
  pinMode(ledPin, OUTPUT);
  pinMode(switch1Pin, INPUT);
  attachInterrupt(0, limitSwitch1Hit, CHANGE);    // Interupt on Pin 2
  attachInterrupt(1, limitSwitch2Hit, CHANGE);    // Interupt on Pin 3
}

void loop() {

}

/* Only excicutes with change of pin voltage */
void limitSwitch1Hit(void){
  ls1 = digitalRead(switch1Pin);
  digitalWrite(ledPin, ls1);
  if(ls1){
    Serial.println("Switch 1 ON");
  }
  else{
    Serial.println("Switch 1 OFF");
  }
}

/* Only excicutes with change of pin voltage */
void limitSwitch2Hit(void){
  ls2 = digitalRead(switch2Pin);
  if(ls2){
    Serial.println("Switch 2 ON");
  }
  else{
    Serial.println("Switch 2 OFF");
  }
}

