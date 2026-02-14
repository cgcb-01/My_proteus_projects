#include <Keypad.h>
#include <LiquidCrystal.h>
#include <EduIntro.h>

LM35 lm35(A0);
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

int fan = 9;  

void setup()
{
  lcd.begin(16, 2);
  lcd.print("Welcome");
  delay(2000);  
  lcd.clear();
  
  pinMode(fan, OUTPUT);
  analogWrite(fan, 0); 
}

void loop()
{
  double tempC = lm35.readCelsius();
  int fanSpeed = 0;  /
  
  lcd.clear();  
  if (tempC <= 12) {
    fanSpeed = 0;  
  }
  else if (tempC > 12 && tempC <= 25) {
    fanSpeed = 45;  
  }
  else if (tempC > 25 && tempC <= 30) {
    fanSpeed = 65;  
  }
  else if (tempC > 30 && tempC <= 35) {
    fanSpeed = 100;  
  }
  else if (tempC > 35 && tempC <= 40) {
    fanSpeed = 150;  
  }
  else {
    fanSpeed = 255;  
  }
  
  analogWrite(fan, fanSpeed);
  
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(tempC, 1); 
  lcd.print(" C");
  

  lcd.setCursor(0, 1);
  lcd.print("Fan Speed: ");
  lcd.print(map(fanSpeed, 0, 255, 0, 100));  
  lcd.print("%");
  
  delay(1000);  
}