#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

//initialize pins
#define sensorPower 7
#define sensorPin A0

int val = 0;
int prev = 0;

// set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27,20,4);  

void setup()
{
  // Set D7 as an OUTPUT
  pinMode(sensorPower, OUTPUT);
  
  // Set to LOW so no power flows through the sensor
  digitalWrite(sensorPower, LOW);
  
  Serial.begin(9600);
  // initialize the lcd
  lcd.begin();                       
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(1,0);
  lcd.print("Water Level:");
}


void loop()
{
  //get the reading from the function below and print it
  int level = readSensor();

  //Update LCD screen
  //Check if water level changed.
  if(prev != level){
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("Water Level:");
    lcd.setCursor(1,1);
    lcd.print(level);
    prev = level;
  }
  
  //Sleep 1s.
  delay(1000);
}


//This is a function used to get the reading
int readSensor() {
  // Turn the sensor ON
  digitalWrite(sensorPower, HIGH);
  // wait 10 milliseconds  
  delay(10);              
  // Read the analog value form sensor
  val = analogRead(sensorPin);    
  // Turn the sensor OFF
  digitalWrite(sensorPower, LOW);
  // Return current reading
  return val;             
}
