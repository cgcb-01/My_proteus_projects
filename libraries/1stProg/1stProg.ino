
#include <Keypad.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const byte ROWS = 4; 
const byte COLS = 4; 
char keys[ROWS][COLS] = {
  {'1','2','3','+'},
  {'4','5','6','-'},
  {'7','8','9','*'},
  {'C','0','=','/'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {A0, A1, A2, A3};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

String num1 = "", num2 = "", op = "";
boolean firstNum = true;

void setup() {
  lcd.begin(16, 2);
  lcd.print("Calculator Ready");
  delay(1000);
  lcd.clear();
}

void loop() {
  char key = keypad.getKey();
  if (key) {
    if (key == '+' || key == '-' || key == '*' || key == '/') {
      op = key;
      firstNum = false;
      lcd.clear();
    } else if (key == '=') {
      int n1 = num1.toInt();
      int n2 = num2.toInt();
      int result;
      if (op == "+") result = n1 + n2;
      else if (op == "-") result = n1 - n2;
      else if (op == "*") result = n1 * n2;
      else if (op == "/") result = n1 / n2;

      lcd.clear();
      lcd.print("Result: ");
      lcd.print(result);
      delay(2000);
      lcd.clear();
      num1 = num2 = op = "";
      firstNum = true;
    } else if (key == 'C') {
      lcd.clear();
      num1 = num2 = op = "";
      firstNum = true;
    } else {
      if (firstNum) num1 += key;
      else num2 += key;
      lcd.print(key);
    }
  }
}
