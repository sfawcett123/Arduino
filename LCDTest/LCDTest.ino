#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
  lcd.init();                      // initialize the lcd 

  lcd.backlight();
  lcd.setCursor(3,0);
  lcd.print("Hello, world!");
  lcd.setCursor(2,1);
  lcd.print("Test LCD display");
   lcd.setCursor(8,2);
  lcd.print("2022");
   lcd.setCursor(2,3);
  lcd.print("Steven Fawcett");
}


void loop()
{
}