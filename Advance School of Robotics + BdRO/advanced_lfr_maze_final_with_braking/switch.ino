int push() {
  int count = 0;
p:  int t = 0;
  if (digitalRead(sw) == 0) {
    digitalWrite(12, HIGH);
    while (digitalRead(sw) == 0) {
      delay(1); t++;
    }
    digitalWrite(12, LOW);
    if (t > 15) {
      count++;
      t = 0;
      while(digitalRead(sw) == 1){
        delay(1); t++;
        if(t>1000) break;
      }
      if(t<1000) goto p;
    }
  }
  return count;
}
