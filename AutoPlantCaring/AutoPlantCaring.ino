#include <Wire.h>  // Arduino IDE built-in library
#include <LiquidCrystal_I2C.h> // Arduino IDE built-in library

#define MOISTURE_SENSOR A1
#define SPRINKLE_PORT 4

//variables
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  //congif LCD I2C
int val;
bool tooDry = false;
const int TOO_DRY_VALUE = 200;
const int TOO_WET_VALUE = 350;
char  str[8]; 

void setup()
{
  Serial.begin(9600);

  //initial LCD
  lcd.begin(20, 4);
  lcd.backlight();
}


void loop ()
{
  val = analogRead(MOISTURE_SENSOR); 
  if (val < TOO_DRY_VALUE) {
    tooDry = true;
  } 

  if (val > TOO_WET_VALUE) {
    tooDry = false;
  }
  
  serialPrint();
  drawLCD();
  delay(1000);
}
void serialPrint() {
  Serial.print("Moisture Sensor Value:");
  Serial.println(val);
  if (tooDry) {
    Serial.println("TOO DRY        ");
  } else {
    Serial.println("GOOD");
  }
}
void drawLCD()
{
  lcd.setCursor(0, 0); 
  lcd.print("Moisture Value:");
  
  sprintf(str, "%5d", val);  
  lcd.print(str);
  lcd.setCursor(0, 2); 
  if (tooDry) {
    lcd.print("TOO DRY    ");
    sprinkle ();
  } else {
    lcd.print("GOOD       ");
  }

}
void sprinkle () {
  Serial.print("Going to sprinkle for 2 seconds.");
  digitalWrite(SPRINKLE_PORT, HIGH);
  delay(2000);
  digitalWrite(SPRINKLE_PORT, LOW);
  Serial.print("Finish sprinkling.");
}

