#include "Arduino.h"
#include "DHT.h"

#define DHTPIN 9
#define DHTTYPE DHT22 //DHT11, DHT21, DHT22
#define DELAYTIME 1000 //700ms delay until next value is generated
#define LED_RED 10
#define LED_GREEN 11
#define LED_BLUE 12
int i;

DHT dht(DHTPIN, DHTTYPE);

//The setup function is called once at startup of the sketch
void setup()
{
// Add your initialization code here
	Serial.begin(9600);
	Serial.println("DHT22 - Temperature/Humidity Measurement");

	dht.begin();

	pinMode(LED_RED, OUTPUT);
	pinMode(LED_GREEN, OUTPUT);
	pinMode(LED_BLUE, OUTPUT);
}

// The loop function is called in an endless loop
void loop()
{
//Add your repeated code here
	float humi = dht.readHumidity();
	float temp = dht.readTemperature();

	for (i = 0; i < 2; ++i)
	{
		if (isnan(humi) || isnan(temp))
		{
			Serial.println("Error while reading sensor!");
		}
		else
		{
		    Serial.print("Humidity: ");
		    Serial.print(humi);
		    Serial.print(" %rH\t");
		    Serial.print("Temperature: ");
		    Serial.print(temp);
		    Serial.println("�C");
		}

		delay(2*DELAYTIME);
	}

	if (humi >= 60)
	{
		analogWrite(LED_RED, 255);
		analogWrite(LED_GREEN, 0);
		analogWrite(LED_BLUE, 0);
	}
	else if (humi >= 50){
		analogWrite(LED_RED, 255);
		analogWrite(LED_GREEN, 50);
		analogWrite(LED_BLUE, 0);
	}
	else if (humi >= 20){
		analogWrite(LED_RED, 0);
		analogWrite(LED_GREEN, 255);
		analogWrite(LED_BLUE, 0);
	}
	else
	{
		analogWrite(LED_RED, 0);
		analogWrite(LED_GREEN, 0);
		analogWrite(LED_BLUE, 255);
	}

	delay(DELAYTIME);

	digitalWrite(LED_RED, LOW);
	digitalWrite(LED_GREEN, LOW);
	digitalWrite(LED_BLUE, LOW);
}
