#include <Wire.h>
#include <LiquidCrystal_I2C.h>


unsigned long time;
 
// The LCD constructor - address shown is 0x27 - may or may not be correct for yours
// Also based on YWRobot LCM1602 IIC V1
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 

int potentiometerSource = 7;
int potentiometerKnob = 0;
int oldValue = 500;

long secondsPerDay = 86400;
long totalSeconds = 0;

void setup()
{
  lcd.begin(20,4);
  lcd.backlight();
  pinMode(potentiometerSource, OUTPUT);
  digitalWrite(potentiometerSource, HIGH);
}
 
 
void loop()
{
  int newValue = analogRead(potentiometerKnob);

  if (newValue > 1000) {
    newValue = 1000;
  } else if (newValue < 10) {
    newValue = 10;
  }
  if (newValue - oldValue > 3 || oldValue - newValue > 3) {
    oldValue = newValue;
    
    lcd.setCursor(0,0);
    lcd.print("R =      ");
    lcd.setCursor(4,0);
    lcd.print(oldValue);

    totalSeconds = 87.2727 * (oldValue - 10);    
  } else {
    delay(1000);
    totalSeconds = (totalSeconds + 1) % secondsPerDay;

    int seconds = (totalSeconds % 60);
    int minutes = (totalSeconds % 3600) / 60;
    int hours   = (totalSeconds % 86400) / 3600;
    
    lcd.setCursor(2,2);
    lcd.print("Hora > ");
    if (hours < 10) lcd.print(0);
    lcd.print(hours);
    lcd.print(":");
    if (minutes < 10) lcd.print(0);
    lcd.print(minutes);
    lcd.print(":");
    if (seconds < 10) lcd.print(0);
    lcd.print(seconds);
  }
}
