void snake_game() {
  bool menu = 1;
  while (digitalRead(mb) == HIGH) {
    display.clearDisplay();
    text("GAME MODE?", 04, 0);
    text("   EASY   ", 04, 25);
    text("   HARD   ", 04, 50);
    (dl == 100) ? text(">>      <<", 04, 25) : text(">>      <<", 04, 50);
    display.display();
    if (digitalRead(ub) == LOW) dl = 50;
    else if (digitalRead(db) == LOW) dl = 100;
  }
  while (digitalRead(mb) == LOW);
  while (digitalRead(mb) == HIGH) {
r:  if (eat == 1) {
      food();
      digitalWrite(buzzer, HIGH);
    }
    else digitalWrite(buzzer, LOW);
    draw();
    motion();
    button();
    for (short int i = 1; i < len ; i ++)
      if (pos[0] == pos[i]) {
        digitalWrite(buzzer, LOW);
        if (game_over(len - 4) == 1) {
          len = 4; return;
        }
        len = 4;
      }
  }
  while (digitalRead(mb) == LOW);
  while (digitalRead(mb) == HIGH) {
    display.clearDisplay();
    text("GAME PAUSE", 04, 0);
    text("  RESUME  ", 04, 25);
    text("   EXIT   ", 04, 50);
    (menu == 1) ? text(">        <", 04, 25) : text(">        <", 04, 50);
    display.display();
    if (digitalRead(ub) == LOW) menu = 0;
    else if (digitalRead(db) == LOW) menu = 1;
  }
  while (digitalRead(mb) == LOW);
  if (menu == 1) goto r;
  len = 4;
}

void draw() {
  for (short i = 0; i < len; i++) display.fillRect((pos[i] / 100) * 3, (pos[i] % 100) * 3, 3, 3, WHITE);
  for (short i = 0; i < len - 1; i++)
    if ((pos[i + 1] / 100) - (pos[i] / 100) <= 2 && (pos[i + 1] / 100) - (pos[i] / 100) >= -2 && (pos[i + 1] % 100) - (pos[i] % 100) <= 2 && (pos[i + 1] % 100) - (pos[i] % 100) >= -2)
      display.fillRect(((pos[i] / 100) + ((pos[i + 1] / 100) - (pos[i] / 100)) / 2) * 3, ((pos[i] % 100) + ((pos[i + 1] % 100) - (pos[i] % 100)) / 2) * 3, 3, 3, WHITE);
  display.fillRect(foodx * 3, foody * 3, 3, 3, WHITE);
  display.display(); display.clearDisplay();
}

void motion() {
  int posx = pos[0] / 100;
  int posy = pos[0] % 100;
  for (int i = len ; i > 0; i--) pos[i] = pos[i - 1];
  if (dir == 1) posx -= 2;
  else if (dir == 3) posx += 2;
  else if (dir == 2) posy -= 2;
  else if (dir == 4) posy += 2;
  if (posx > 40) posx = 0;
  else if (posx < 0) posx = 40;
  if (posy > 20) posy = 0;
  else if (posy < 0) posy = 20;

  pos[0] = posx * 100 + posy;
  if (pos[0] == 100 * foodx + foody) {
    eat = 1; len++;
  }
}

void button() {
  m81 = m82 = millis();
  while (m82 - m81 < dl) {
    m82 = millis();
    if (digitalRead(ub) == LOW && s_b == 0) {
      dir++; s_b = 1; delay(5);
    }
    if (digitalRead(db) == LOW && s_b == 0) {
      dir--; s_b = 1; delay(5);
    }
    if (digitalRead(ub) == HIGH && digitalRead(db) == HIGH) s_b = 0;
    if (dir < 1) dir = 4;
    else if (dir > 4) dir = 1;
    if(m82 - m81 < 20) digitalWrite(buzzer, LOW);
  }
}

void food() {
  eat = 0;
f:  foodx = (rand() % 20) * 2;
  foody = (rand() % 10) * 2;
  for (short int i = 0; i < len ; i ++) if (pos[i] == 100 * foodx + foody) goto f;
}

int game_over(int a) {
  value = String(a, 10);
  int menu = 0;
  beeping(3);
  while (digitalRead(mb) == HIGH) {
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    text("GAME OVER!", 04, 0);
    text("SCORE:" + value, 04, 25);
    display.setTextSize(1);
    text(" PLAY AGAIN", 04, 55);
    text("              EXIT", 04, 55);
    (menu == 0) ? text(">          <", 04, 55) : text("             >    <", 04, 55);
    display.display();
    if (digitalRead(ub) == LOW) menu = 1;
    else if (digitalRead(db) == LOW) menu = 0;
  }
  while (digitalRead(mb) == LOW);
  display.setTextSize(2);
  return menu;
}