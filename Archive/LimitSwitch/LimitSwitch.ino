#define switch1 2
#define switch2 3

void setup() {
  Serial.begin(9600);
  Serial.println("Limit Switch");
  pinMode(switch1, INPUT);
  pinMode(switch2, INPUT);
}

void loop() {
 //if(digitalRead(switch1)){
  Serial.println(digitalRead(2));
 //}
 if(digitalRead(switch2)){
  //Serial.println("Switch 2 on");
 }
}
