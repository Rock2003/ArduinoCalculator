#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Key.h>
#include <Keypad.h>

int lcdposition = 0;
String operation = "";
String operation1 = "";
String operation2= "";

//rows and clumns
const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', '+'},
  {'4', '5', '6', '-'}, 
  {'7', '8', '9', '*'}, 
  {'C', '0', '=', '/'}
};

byte rowPins[ROWS] = {5, 4, 3, 2};
byte colPins[COLS] = {9, 8, 7, 6};

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

LiquidCrystal_I2C lcd (0x27, 16, 2);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin();
  lcd.begin(16,2);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.backlight();
}

void loop() {
  // put your main code here, to run repeatedly:
  char custom = customKeypad.getKey();

  if(isIn(custom)) {
    printer(custom);
  }
}

void printer(char num) {
  if(num == 'C') {
    lcd.clear();
    lcd.setCursor(0,0);
    lcdposition = 0;
    operation = "";
    return;
  }
  if(lcdposition == 0) {
    lcd.setCursor(0,0);
    lcd.print(num);
    lcdposition++;
  }else if(lcdposition < 16){
    lcd.print(num); 
    lcdposition++; 
  } else if(lcdposition == 16) {
    lcd.setCursor(0,1);
    lcd.print(num);
    lcdposition++;
  } else if(lcdposition < 31) {
    lcd.print(num);
    lcdposition++; 
  } else if(lcdposition == 31) {
    lcd.print(num);
    lcd.setCursor(0,0);
    lcdposition = 0;
  }
  if(num == '=') {
    int x = doMath(operation);
    lcd.print(x);
    operation = "";
  }
  operation+=num;
  Serial.println(operation);
}

bool isIn(char num) {
  for(int i =0; i < 4; i++) {
    for(int j=0; j<4 ;j++) {
      if(hexaKeys[i][j] == num) {
        return true; 
      }
    }
  }
  return false;
}

int doMath(String exp) {
  int last = 0;
  int result = 0;
  char sign = 'x';
  for(int i = 0; i<exp.length(); i++) {
    char l = exp.charAt(i);
    
    if( ( l == '+' || l == '-' || l == '*' || l == '/') && last ==0 ) {
      result = exp.substring(last, i).toInt();
      last = i+1;
      sign = l;
    } else if(l == '+' || l == '-' || l == '*' || l == '/') {
      if(sign == '+' ) {
        result += exp.substring(last, i).toInt();
      }else if(sign == '-' ) {
        result -= exp.substring(last, i).toInt();
      }else if(sign == '*' ) {
        result *= exp.substring(last, i).toInt();
      }else if(sign == '/') {
        result /= exp.substring(last, i).toInt();
      }
      last = i+1;
      sign = l;
    }
  }
  if(sign == '+' ) {
        result += exp.substring(last).toInt();
  }else if(sign == '-' ) {
        result -= exp.substring(last).toInt();
  }else if(sign == '*' ) {
        result *= exp.substring(last).toInt();
  }else if(sign == '/') {
        result /= exp.substring(last).toInt();
  }
  return result;
}
