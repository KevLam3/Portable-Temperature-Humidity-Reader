// Including the library code:
#include <LiquidCrystal.h>
#include "DHT.h"

// Defining the type of DHT and then setting the pin that it will be on
#define DHTPIN 7
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Assigning the LCD to pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Setting the pin for the button
const int buttonPinLeft = A4;

// Defining variables
int buttonStateLeft = 0;
String Incoming_value;
float temperature;
float humidity;

void setup() {
  pinMode(buttonPinLeft, INPUT);
  Serial.begin(9600);
}

void loop() {
  // 
  buttonStateLeft = digitalRead(buttonPinLeft);
  if (buttonStateLeft == HIGH ) {
    // set up the LCD's number of columns and rows and the DHT
    lcd.begin(16, 2);
    dht.begin();

    // Print a message to the LCD.
    lcd.print("Temp:  Humidity:");
    for (int i = 0; i < 20; i++) {
      delay(500);
      // set the cursor to column 0, line 1
      // (note: line 1 is the second row, since counting begins with 0):
      lcd.setCursor(0, 1);
      // reading humidity
      humidity = dht.readHumidity();
      // reading temperature (true = Fahrenheit | false = Celsius)
      temperature = dht.readTemperature(true);
      lcd.print(temperature);
      lcd.setCursor(7, 1);
      lcd.print(humidity);
    }
    lcd.clear();
  }

  // 
  if (Serial.available() > 0)
  {
    dht.begin();
    Incoming_value = Serial.readString();      //Read the incoming data and store it into variable Incoming_value
    Incoming_value.trim();
    if (Incoming_value == "temp") {           //Checks whether value of Incoming_value is equal to 1
      temperature = dht.readTemperature(true);
      Serial.println("Temperature is ");  //If value is 1 then LED turns ON
      Serial.print(temperature);
    }
    else if (Incoming_value == "hum")  {    //Checks whether value of Incoming_value is equal to 0
      humidity = dht.readHumidity();
      Serial.println("Humidity is ");
      Serial.print(humidity);  //If value is 0 then LED turns OFF
    }
  }

}
