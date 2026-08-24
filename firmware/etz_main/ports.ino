void init_pin_D(int mode) {
  if (mode == 1) pinMode(D_PIN, INPUT);
  else if (mode == 2) pinMode(D_PIN, INPUT_PULLUP);
  else pinMode(D_PIN, OUTPUT);
}
void init_pin_A() {
  pinMode(A_PIN, INPUT);
}
void init_pin_UART() {
  SERIAL_PIN.begin(UART_SPEED);
}

int get_value_D() {
  return digitalRead(D_PIN);
}
int get_value_A() {
  return analogRead(A_PIN);
}
void get_value_UART(int &value) {
  if (SERIAL_PIN.available()) {
    value = SERIAL_PIN.parseInt();
  }
}
void get_string_UART(String &line) {
  if (SERIAL_PIN.available()) {
    line = SERIAL_PIN.readStringUntil('\n');
  }
}
void get_char_UART(char &symbol) {
  if (SERIAL_PIN.available()) {
    symbol = SERIAL_PIN.read();
  }
}
void clear_UART(){
  while (SERIAL_PIN.available()) {
    SERIAL_PIN.read();
  }
}

/*
void parse_UART(String format){
  int found = sscanf(msg.c_str(), format, &xValue, &yValue);

  int xValue = 0;
  int yValue = 0;
  static String value = "";
  static String last = "";
  get_string_UART(value);
  if (last != value) {
    sscanf(value.c_str(), "x:%d y:%d", &xValue, &yValue);
    Serial.println(value);
    Serial.print(xValue);
    Serial.print("\t");
    Serial.println(yValue);
  }
  delay(500);
  last = value;
}*/

void write_pin_D(bool level) {
  digitalWrite(D_PIN, level);
}
void write_pin_UART(int value) {
  SERIAL_PIN.write(value);
}
void print_pin_UART(char symbol) {
  SERIAL_PIN.print(symbol);
}