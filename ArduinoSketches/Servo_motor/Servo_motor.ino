#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Servo.h>

LiquidCrystal lcd(A4, A5, A3, A2, A1, A0);
Servo myservo;

const byte ROWS = 4; 
const byte COLS = 3; 

char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

byte rowPins[ROWS] = {3,2,1,0}; 
byte colPins[COLS] = {4,5,6}; 

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

String password = "3732";  
String input = "";

int buzzer = 8;
int servoPin = 9;

void setup() {
  lcd.begin(16, 2);
  lcd.print("Enter Password:");
  myservo.attach(servoPin);
  myservo.write(0);  // Door closed
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, LOW);
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    if (key == '#') { // '#' used as Enter key
      if (input == password) {
        lcd.clear();
        lcd.print("Access Granted");
        myservo.write(90);     // Door opens
        delay(3000);
        myservo.write(0);      // Door closes
        lcd.clear();
        lcd.print("Enter Password:");
      } else {
        lcd.clear();
        lcd.print("Access Denied!");
        digitalWrite(buzzer, HIGH);
        delay(1000);
        digitalWrite(buzzer, LOW);
        lcd.clear();
        lcd.print("Enter Password:");
      }
      input = ""; // Reset input
    } 
    else if (key == '*') { // '*' to clear input
      input = "";
      lcd.clear();
      lcd.print("Enter Password:");
    } 
    else {
      input += key;
      lcd.setCursor(0, 1);
      for (int i = 0; i < input.length(); i++) lcd.print('*'); // mask password
    }
  }
}

