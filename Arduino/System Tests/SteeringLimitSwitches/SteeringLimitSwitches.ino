#define switchLeft 2
#define switchRight 3

void setup()
{
	Serial.begin(9600);
	Serial.println("Limit Switch");
	pinMode(switchLeft, INPUT);
	pinMode(switchRight, INPUT);
}

void loop()
{
	Serial.print("Left Switch: ");
	Serial.print(digitalRead(switchLeft));
	Serial.print(" Right Switch: ");
	Serial.println(digitalRead(switchRight));
	delay(50);
}
