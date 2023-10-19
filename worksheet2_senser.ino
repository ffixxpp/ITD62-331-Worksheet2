#include "DHT.h"
#include "Wire.h"
#include "LiquidCrystal_I2C.h"

#define DHTPIN D4
#define DHTTYPE DHT11

LiquidCrystal_I2C lcd(0x3F, 16, 2);
DHT dht(DHTPIN, DHTTYPE);

void setup()
{
    Serial.begin(115200);
    dht.begin();
    lcd.begin();
    lcd.backlight();
}


void loop()
{
    float tempCelsius = dht.readTemperature();
    float tempFahrenheit = dht.readTemperature(true);
    float humidity = dht.readHumidity();

    if (isnan(tempCelsius) || isnan(tempFahrenheit) || isnan(humidity))
    {
        Serial.println("Failed to read sensor data!");
        return;
    }
    else
    {
        lcd.clear();

        lcd.setCursor(0, 0);
        lcd.print("Temp: ");
        lcd.print(tempCelsius, 1);
        lcd.setCursor(11, 0);
        lcd.print("C");

        lcd.setCursor(0, 1);
        lcd.print("Humi: ");
        lcd.print(humidity, 1);
        lcd.setCursor(11, 1);
        lcd.print("%");

        Serial.print("Temp: ");
        Serial.print(tempCelsius, 1);
        Serial.print(" C, ");
        Serial.print("Humi: ");
        Serial.print(humidity, 1);
        Serial.println("");

        delay(200);
    }
}
