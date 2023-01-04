void mos(short int a , short int b) {
  if (a >= 0) {
    analogWrite(lmf, a);
    analogWrite(lmb, 0);
  }
  else if (a < 0) {
    a = -a;
    analogWrite(lmb, a);
    analogWrite(lmf, 0);
  }
  if (b >= 0) {
    analogWrite(rmf, b);
    analogWrite(rmb, 0);
  }
  else if (b < 0) {
    b = -b;
    analogWrite(rmb, b);
    analogWrite(rmf, 0);
  }
  return ;
}

void motorSpeedB(short int a, short int b) {
  mos(-a, -b);
}

void motorSpeedR(short int a, short int b) {
  if (a < lowest_speed) a = lowest_speed;
  if (b < lowest_speed) b = lowest_speed;
  mos(a, -b);
}

void motorSpeedL(short int a, short int b) {
  if (a < lowest_speed) a = lowest_speed;
  if (b < lowest_speed) b = lowest_speed;
  mos(-a, b);
}

void braking_mechanism(float a) {
  motorSpeedB(10 * spl, 10 * spr);
  brake = cl / d;
  delay(a * brake);
  k30 = 0;
  k90 = 0;
  mov = 0;
  cross = 0;
  cl = base;
  k = 0;
}

void head_light(int a) {
  if (a == 1) {
    digitalWrite(head_left1, HIGH);
    digitalWrite(head_right1, HIGH);
    digitalWrite(head_left2, HIGH);
    digitalWrite(head_right2, HIGH);
  }
  else {
    digitalWrite(head_left1, LOW);
    digitalWrite(head_right1, LOW);
    digitalWrite(head_left2, LOW);
    digitalWrite(head_right2, LOW);
  }
}
