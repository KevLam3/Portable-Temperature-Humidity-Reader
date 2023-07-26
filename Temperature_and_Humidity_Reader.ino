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
  // This is for the physical button 
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

  // This is for any digtial input (via Serial Monitor or an app in the future)
  if (Serial.available() > 0)
  {
    dht.begin();
    //Read the incoming data
    Incoming_value = Serial.readString();      
    Incoming_value.trim();
    //Checks whether value of Incoming_value is equal to "temp"
    if (Incoming_value == "temp") {     
      // reading temperature (true = Fahrenheit | false = Celsius)      
      temperature = dht.readTemperature(true);
      Serial.println("Temperature is ");  //If true, display the temperature 
      Serial.print(temperature);
    }
    //Checks whether value of Incoming_value is equal to "temp"
    else if (Incoming_value == "hum")  {    
      humidity = dht.readHumidity();
      Serial.println("Humidity is "); // If true, display the humidity
      Serial.print(humidity);  
    }
  }

}
