/*void check_x() {
  static bool last_state = 0;
  uint32_t timer = millis();
  while (millis() - timer < 2000) {
    bool current_state = digitalRead(24);
    if (current_state == 0 && last_state == 1) {
      delay(5);
      timer = millis();
      x++;
    }
    last_state = current_state;
  }
  x %= 10;
}*/
/*button_pressed = 0;
  while (!button_pressed){
    Serial.print(get_value_D());
    Serial.print("\t");
    Serial.print(get_value_A());
    Serial.print("\t");
    Serial.println(get_value_UART());
  }*/

//костыльный фрактал
double list[18];
bool completed = false;

void draw_3_triangle(double x1, double y1, double x2, double y2, double x3, double y3) {
  double x1_new = (x1 + x3) / 2, y1_new = (y1 + y3) / 2, x2_new = x3, y2_new = y2, x3_new = (x3 + x2) / 2, y3_new = (y2 + y3) / 2;
  double x1_last = x1_new, y1_last = y1_new, x2_last = x2_new, y2_last = y2_new, x3_last = x3_new, y3_last = y3_new;
  if (!completed) {
    list[0] = x1, list[1] = y1, list[2] = (x1 + x2) / 2, list[3] = y2, list[4] = (x1 + x3) / 2, list[5] = (y1 + y3) / 2;
    list[6] = (x1 + x2) / 2, list[7] = y1, list[8] = x2, list[9] = y2, list[10] = (x2 + x3) / 2, list[11] = (y2 + y3) / 2;
    list[12] = (x1 + x3) / 2, list[13] = (y1 + y3) / 2, list[14] = (x3 + x2) / 2, list[15] = (y2 + y3) / 2, list[16] = x3, list[17] = y3;
    completed = true;
  }
  draw_triangle(x1_new, y1_new, x2_new, y2_new, x3_new, y3_new);

  x1_new = (x1_last + x1) / 2, y1_new = (y1_last + y1) / 2;
  x2_new = (x2_last + x1) / 2, y2_new = (y2_last + y2) / 2;
  x3_new = (x3_last + x1) / 2, y3_new = (y3_last + y2) / 2;
  draw_triangle(x1_new, y1_new, x2_new, y2_new, x3_new, y3_new);
  x1_last = x1_new, y1_last = y1_new, x2_last = x2_new, y2_last = y2_new, x3_last = x3_new, y3_last = y3_new;

  x1_new = (x1 + x3) / 2, y1_new = (y1 + y3) / 2, x2_new = x3, y2_new = y2, x3_new = (x3 + x2) / 2, y3_new = (y2 + y3) / 2;
  x1_last = x1_new, y1_last = y1_new, x2_last = x2_new, y2_last = y2_new, x3_last = x3_new, y3_last = y3_new;
  x1_new = (x1_last + x2) / 2, y1_new = (y1_last + y1) / 2;
  x2_new = (x2_last + x2) / 2, y2_new = (y2_last + y2) / 2;
  x3_new = (x3_last + x2) / 2, y3_new = (y3_last + y2) / 2;
  draw_triangle(x1_new, y1_new, x2_new, y2_new, x3_new, y3_new);
  x1_last = x1_new, y1_last = y1_new, x2_last = x2_new, y2_last = y2_new, x3_last = x3_new, y3_last = y3_new;

  x1_new = (x1 + x3) / 2, y1_new = (y1 + y3) / 2, x2_new = x3, y2_new = y2, x3_new = (x3 + x2) / 2, y3_new = (y2 + y3) / 2;
  x1_last = x1_new, y1_last = y1_new, x2_last = x2_new, y2_last = y2_new, x3_last = x3_new, y3_last = y3_new;
  x1_new = (x1_last + x3) / 2, y1_new = (y1_last + y3) / 2;
  x2_new = x2_last, y2_new = y3_last;
  x3_new = (x3_last + x3) / 2, y3_new = (y3_last + y3) / 2;
  draw_triangle(x1_new, y1_new, x2_new, y2_new, x3_new, y3_new);
  x1_last = x1_new, y1_last = y1_new, x2_last = x2_new, y2_last = y2_new, x3_last = x3_new, y3_last = y3_new;
}


int get_value(String line, String marker) {
  String result = "";
  int start = line.indexOf(marker) + marker.length();
  for (int i = start; i < line.length(); i++) {
    if (isDigit(line[i])) result += line[i];
    else break;
  }
  return result.toInt();
}
float get_float_value(String s, String key) {
  String result = "";
  for (int i = s.indexOf(key) + key.length(); i < s.length(); i++) {
    if (isDigit(s[i])) {
      result += s[i];
    } else if (s[i] == '.') {
      result += '.';
    } else {
      break;
    }
  }
  return result.toFloat();
}

void hard_task_reg() {
  int x = 0;
  int digits[10] = { 0B00000, 0B10000, 0B11000, 0B11100, 0B11110, 0B11111, 0B01111, 0B00111, 0B00011, 0B00001 }, digit = 0;
  uint32_t time[10];
  uint32_t wait_timer = 0;

  bool curr_state, last_state = 1;
  while (!digitalRead(24))
    ;

  uint32_t timer = millis();
  for (int i = 0; i < 9; i++) {
    curr_state = digitalRead(24);
    timer = millis();
    while (curr_state == last_state) {
      last_state = curr_state;
      curr_state = digitalRead(24);
      delay(5);
    }
    last_state = curr_state;
    time[i] = millis() - timer;
    if (i % 2 == 1) wait_timer += (millis() - timer) / 4;
    Serial.println(time[i]);
  }
  for (int i = 0; i < 5; i++) {
    bitWrite(digit, 4 - i, 1 - (time[i * 2] >= wait_timer / 2));
  }
  Serial.println(digit, BIN);
  for (; x < 11; x++) {
    if (x == 10 || digit == digits[x]) break;
  }
  Serial.println(x);

  find_line();

  set_pos(30 + 1, 50);
  int point_length = 3;
  if (x <= 5) {
    for (int i = 0; i < x; i++) {
      down_handle();
      move(point_length - 1, 0);
      up_handle();
      move(point_length * 3 + 2, 0);
    }
    for (int i = 0; i < 5 - x; i++) {
      down_handle();
      move(point_length * 3 - 1, 0);
      up_handle();
      move(point_length * 3 + 2, 0);
    }
  } else {
    for (int i = 0; i < x - 5; i++) {
      down_handle();
      move(point_length * 3 - 1, 0);
      up_handle();
      move(point_length * 3 + 2, 0);
    }
    for (int i = 0; i < 10 - x; i++) {
      down_handle();
      move(point_length - 1, 0);
      up_handle();
      move(point_length * 3 + 2, 0);
    }
  }

  home();
}

// штриховка прямоугольника
void shtrihovka() {
  int x0 = 100, y0 = 10, size_x = 20, size_y = 100;
  draw_rect(x0, y0, size_x, size_y);

  set_pos(x0 + size_x, y0 - size_x);
  int y = y0 - size_x, step_y = 10;
  while (y < size_y + y0) {
    while (x_curr > x0) {
      if (x_curr < x0 + size_x && x_curr > x0 && y_curr < size_y + y0 && y_curr > y0) {
        Vx = 0, Vy = 0;
        wait();
        down_handle();
      } else {
        Vx = 0, Vy = 0;
        wait();
        up_handle();
      }
      Vx = -V_FUNC;
      Vy = V_FUNC;
      wait();
    }
    stop_motor();
    up_handle();
    y += step_y;
    set_pos(size_x + x0, y);
  }
}

//судоку
void sudoku(){
  find_line();
  int x_wish[3] = { 2, 2, 2 }, y_wish[3] = { 2, 2, 2 };
  set_pos(45.5, 45.5);
  for (int x = 0; x < 3; x++) {
    int digit = 0;
    delay(1000);
    if (analogRead(LINE_SENSOR) > line_value * 0.15) digit++;
    Serial.print(digit);
    move(7.5, 0);
    delay(1000);
    if (analogRead(LINE_SENSOR) > line_value * 0.15) digit += 2;
    Serial.println(digit);
    move(22, 0);
    y_wish[x] = digit;
  }
  set_pos(130, 66.5);
  for (int y = 0; y < 3; y++) {
    int digit = 0;
    delay(1000);
    if (analogRead(LINE_SENSOR) > line_value * 0.15) digit++;
    move(10, 0);
    delay(1000);
    if (analogRead(LINE_SENSOR) > line_value * 0.15) digit += 2;
    move(-10, 30);
    x_wish[y] = digit;
    Serial.println(digit);
  }
  int i = 0;
  bool found = true;
  for (; i < 512; i++) {
    found = true;
    for (int y = 0; y < 3; y++) {
      for (int x = 0; x < 3; x++) {
        if (count_x(i, y) != x_wish[y]) {
          found = false;
        }
        if (count_y(i, x) != y_wish[x]) {
          found = false;
        }
      }
    }
    if (found) break;
  }
  Serial.println(i, BIN);
  for (int z = 0; z < 9; z++) {
    if (bitRead(i, z) == 0) continue;

    draw_circle(49 + 28.5 * (2 - z % 3), 49 + (2 - z / 3) * 29, 2.5);
  }
}
int count_x(int value, int y0) {
  int summ = 0;
  for (int i = 0; i < 3; i++) {
    if (bitRead(value, i + (2 - y0) * 3)) summ++;
  }
  return summ;
}
int count_y(int value, int x0) {
  int summ = 0;
  for (int i = 0; i < 3; i++) {
    if (bitRead(value, (2 - x0) + i * 3)) summ++;
  }
  return summ;
}


void sort(double *list, int len, bool reverse) {
  for (int i = 0; i < len; i++) {
    for (int j = 0; j < len - i - 1; j++) {
      if (list[j] > list[j + 1]) {
        double value = list[j];
        list[j] = list[j + 1];
        list[j + 1] = value;
      }
    }
  }
  if (reverse) {
    for (int i = 0; i < (len / 2); i++) {
      double value = list[i];
      list[i] = list[len - 1 - i];
      list[len - 1 - i] = value;
    }
  }
}

void find_farest_point(){
  double minX = 1000, minY = 1000, y0 = 40;
  while (y0 < 100) {
    set_pos(20, y0);
    y0 += 5;
    while (x_curr < 150) {
      Vx = 50;
      wait();
      if (analogRead(LINE_SENSOR) > line_value * 0.5) {
        stop_motor();
        if (dist_to_point(0, 0) < dist_to_point(0, 0, minX, minY)) {
          minX = x_curr;
          minY = y_curr;
        }
        break;
      }
    }
  }
  minX -= 5;
  minY -= 20;
  draw_circle(minX, minY, 10);
}
void parse_morze(){
  int summ = 0;
  int x = 0;
  int digits[10] = { 0B00000, 0B10000, 0B11000, 0B11100, 0B11110, 0B11111, 0B01111, 0B00111, 0B00011, 0B00001 }, digit = 0;
  uint32_t time[10];
  uint32_t wait_timer = 0;

  static uint32_t last_call = millis();
  while (millis() - last_call < 4000) {
    if (digitalRead(D_PIN)) last_call = millis();
  }
  summ = 0;

  bool curr_state, last_state = 1;

  uint32_t timer = millis();
  for (int y = 0; y < 5; y++) {
    x = 0;
    digit = 0;
    for (int i = 0; i < 5; i++) {
      while (!digitalRead(D_PIN))
        ;
      curr_state = digitalRead(D_PIN);
      timer = millis();
      while (curr_state == 1) {
        curr_state = digitalRead(D_PIN);
        delay(5);
      }
      time[i] = millis() - timer;
      Serial.println(time[i]);
      delay(300);
    }
    for (int i = 0; i < 5; i++) {
      bitWrite(digit, 4 - i, 1 - (time[i] >= 400));
    }
    Serial.println(digit, BIN);
    for (; x < 11; x++) {
      if (x == 10 || digit == digits[x]) break;
    }
    summ += x;
    Serial.println(x);
  }
  summ %= 10;
  Serial.println();
  Serial.println();
  Serial.println(summ);
  Serial.println();
  Serial.println();
}
void scan(){
  int x0 = 15, y0 = 52 - handle_displacement + 5, dir = 1;
  double pos[2 * 2];
  bool found = false, displacement = 0;
  set_pos(x0, y0);
  for (int i = 0; i < 1; i++) {
    while (y_curr < 175) {
      while (x_curr <= 270 && x_curr >= 12.5) {
        //set_pos(x0, y0);
        Vx = 50 * dir;
        wait();
        x0 += 5;
        if (analogRead(LINE_SENSOR) > line_value * 0.25) {
          stop_motor();
          light(0);
          delay(500);
          light(1);
          delay(500);
          found = true;
          displacement = true;
          break;
        }
      }
      stop_motor();
      if (found) break;
      move(-7.5 * dir, 5 + displacement * 7.5);
      displacement = 0;
      dir *= -1;
    }
    find_point(dir, pos[i * 2], pos[i * 2 + 1], 0.15);
    //draw_circle(pos[0], pos[1], 7.5, 1);
    /*pos[i * 2] = x_curr - 2.5 * dir + 6.7;
    pos[i * 2 + 1] = y_curr - 52 + handle_displacement + 2.75;*/
    move(12 * dir, 0);
    found = false;
  }
  /*move(-2.5 * dir, -52 + handle_displacement + 2.75);
  draw_circle(x_curr, y_curr, 6);*/
  //draw_point((pos[0] + pos[2]) / 2, (pos[1] + pos[3]) / 2);
  //draw_triangle(pos[0], pos[1], pos[2], pos[3], pos[4], pos[5]);
  //draw_line(pos[0], pos[1], pos[2], pos[3]);
  //draw_circle((pos[0] + pos[2]) / 2, (pos[1] + pos[3]) / 2, dist_to_point(pos[0], pos[1], pos[2], pos[3]) / 2);
  draw_circle(pos[0], pos[1], 10, 1);
}

void find_line_size(){
  double y0 = 40, xMin = 50, yMin = 56, xMax = 120, yMax = 102;
  double x = -1, size_x = -1, y = -1, size_y = -1;
  while (x == -1) {
    set_pos_line_sens(20, y0);
    y0 += 25;
    while (x_curr < 130) {
      Vx = 67;
      wait();
      if (analogRead(LINE_SENSOR) > line_value * 0.3) {
        stop_motor();
        x = get_line_sens_pos_x();
        move(20, 0);
        while (analogRead(LINE_SENSOR) > line_value * 0.3) {
          Vx = 67;
          wait();
        }
        stop_motor();
        size_x = get_line_sens_pos_x(1) - x;
        break;
      }
    }
  }
  while (y == -1) {
    set_pos_line_sens(x + 20, 20);
    while (x_curr < 130) {
      Vy = 67;
      wait();
      if (analogRead(LINE_SENSOR) > line_value * 0.3) {
        stop_motor();
        y = get_line_sens_pos_y();
        move(0, 20);
        while (analogRead(LINE_SENSOR) > line_value * 0.3) {
          Vy = 67;
          wait();
        }
        stop_motor();
        size_y = get_line_sens_pos_y(1) - y;
        break;
      }
    }
  }
}