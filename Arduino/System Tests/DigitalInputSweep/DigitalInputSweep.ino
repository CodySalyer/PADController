void setup()
{
	Serial.begin(9600);
	Serial.println("Digital Input Sweep");
	for (int i = 1; i < 13; i++)
	{
		pinMode(i, INPUT);
	}

}

void loop()
{
	Serial.println("Starting Sweep");
	Serial.println("Starting Sweep");
	Serial.println("Starting Sweep");
	Serial.println("Starting Sweep");
	Serial.println("Starting Sweep");
	Serial.println("Starting Sweep");
	int j = 0;
	for (int i = 1; i < 13; i++)
	{
		Serial.print("Item: ");
		Serial.print(i);
		Serial.print(" Value: ");
		j += digitalRead(i);
		Serial.println(digitalRead(i));

		delay(50);
	}
	Serial.println("J VALUE:");
	Serial.println(j);
	delay(500);
}
