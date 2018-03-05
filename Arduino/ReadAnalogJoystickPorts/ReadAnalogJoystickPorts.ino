void setup()
{
	Serial.begin(9600);
	Serial.println("Analog test");
	pinMode(A0, INPUT);
	pinMode(A1, INPUT);
}

void loop()
{
	Serial.print("A0: ");
	Serial.print(analogRead(A0));
	Serial.print(" A1: ");
	Serial.println(analogRead(A1));
	delay(250);
}
