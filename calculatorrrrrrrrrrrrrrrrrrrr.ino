

void setup() {
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
}

void loop() {
  // send data only when you receive data:
  if (Serial.available() > 0) {
    // read the incoming byte:
    String operation = Serial.readString();

    Serial.print("I received: ");
    Serial.println(operation);
    int x = doMath(operation);
    Serial.print("Output: ");
    Serial.println(x);
  }
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
        result += exp.substring(last, i).toInt();
      }else if(sign == '*' ) {
        result += exp.substring(last, i).toInt();
      }else if(sign == '/') {
        result += exp.substring(last, i).toInt();
      }
      last = i+1;
      sign = l;
    }
  }
  return result;
}
