void clock_update() {
  current_time = get_time();
  display_value(current_time);
}

void alarm_update() {
  current_alarm = get_alarm();
  display_value(current_alarm);
}

void date_update() {
  current_date = get_date();
  display_value(current_date);
}

void special_alarm_update_1() {
  s_alarm_1 = get_initial();
  display_value(s_alarm_1);
}

void special_alarm_update_2() {
  s_alarm_2 = get_alarm_2();
  display_value(s_alarm_2);
}
