void line_follow() {
  while (digitalRead(calin) == LOW) {
    check();

    if (sum == 0) {
      if (mov == 1 ) {
        delay(btd);
        if (k30 == 1) {
          digitalWrite(d30, HIGH);
          braking_mechanism();
          while (sensor[1] == 0 && sensor[4] == 0) {
            check();
            motorSpeedR(180, 180);
          }
          motorSpeedL(180, 180);
          delay(br*1.5);
          digitalWrite(d30, LOW);
        }
        else if (k90 == 1) {
          digitalWrite(d90, HIGH);
          braking_mechanism();
          while (sensor[1] == 0 && sensor[4] == 0) {
            check();
            motorSpeedR(180, 180);

          }
          motorSpeedL(180, 180);
          delay(br);
          digitalWrite(d90, LOW);
        }
      }
      else if (mov == 2) {
        delay(btd);
        if (k30 == 2) {
          digitalWrite(d30, HIGH);
          braking_mechanism();
          while (sensor[1] == 0 && sensor[4] == 0) {
            check();
            motorSpeedL(180, 180);
          }
          motorSpeedR(180, 180);
          delay(br*1.5);
          digitalWrite(d30, LOW);
        }
        else if (k90 == 2) {
          digitalWrite(d90, HIGH);
          braking_mechanism();
          while (sensor[1] == 0 && sensor[4] == 0) {
            check();
            motorSpeedL(180, 180);
          }
          motorSpeedR(180, 180);
          delay(br);
          digitalWrite(d90, LOW);
        }
      }
      else if (wall_trigger(1) == 1) wall_follow();
    }//.................................................................end of sum 0

    //..............................................................sum=1||sum=2
    else if (sum == 1 || sum == 2) {
      check();
      if (cross == 1) {
        digitalWrite(d90, HIGH);
        digitalWrite(d30, HIGH);
        braking_mechanism();
        motorSpeedR(180, 180);
        check();
        while (sensor[0] == 1) check();
        while (sensor[0] == 0) check();
        while (sensor[2] == 1 || sensor[3] == 1) check();
        while (sensor[2] == 0 && sensor[3] == 0) check();
        motorSpeedL(180, 180);
        delay(br);
        digitalWrite(d90, LOW);
        digitalWrite(d30, LOW);
      }
      if (cross == 2) {
        digitalWrite(d90, HIGH);
        digitalWrite(d30, HIGH);
        braking_mechanism();
        motorSpeedL(180, 180);
        while (sensor[5] == 1) check();
        while (sensor[5] == 0) check();
        while (sensor[2] == 1 || sensor[3] == 1) check();
        while (sensor[2] == 0 && sensor[3] == 0) check();
        motorSpeedR(180, 180);
        delay(br);
        digitalWrite(d90, LOW);
        digitalWrite(d30, LOW);
      }
      //.............................................................line shuru
      else if (bin == 12) {
        if (k > 0) {
          motorSpeedL(10 * spr, 10 * spl);
          delay(dt);
        }
        else if (k < 0) {
          motorSpeedR(10 * spr, 10 * spl);
          delay(dt);
        }
        k = 0;
        mos(10 * spr, 10 * spl);
        if (cl < peak) cl++;
      }
      else if (bin == 4) {
        mos(9 * spr, 10 * spl);
        if (cl < peak) cl++;
      }

      else if (bin == 8) {
        mos(10 * spr, 9 * spl);
        if (cl < peak) cl++;
      }
      //..................................................left side position
      else if (bin == 6) {
        if (k < 2) {
          motorSpeedR(10 * spr, 10 * spl);
          delay(dt);
          k = 2;
        }
        mos(5 * spr, 10 * spl);
      }
      else if (bin == 2) {
        if (k < 3) {
          motorSpeedR(10 * spr, 10 * spl);
          delay(dt);
          k = 3;
        }
        mos(3 * spr, 10 * spl);
      }
      else if (bin == 3) {
        if (k < 4) {
          motorSpeedR(10 * spr, 10 * spl);
          delay(dt);
          k = 4;
        }
        mos( -3 * spr, 10 * spl);
        //mov = 1;
      }
      else if (bin == 1) {
        if (k < 5) {
          motorSpeedR(10 * spr, 10 * spl);
          delay(dt);
          k = 5;
        }
        mos(-5 * spr, 10 * spl);
        mov = 1;
      }
      // ..................................................dan side shesh
      // .....................................................bam side shuru
      else if (bin == 24) {
        if (k > -2) {
          motorSpeedL(10 * spr, 10 * spl);
          delay(dt);
          k = -2;
        }
        mos(10 * spr, 5 * spl);
      }
      else if (bin == 16) {
        if (k > -3) {
          motorSpeedL(10 * spr, 10 * spl);
          delay(dt);
          k = -3;
        }
        mos(10 * spr, 3 * spl);
      }
      else if (bin == 48) {
        if (k > -4) {
          motorSpeedL(10 * spr, 10 * spl);
          delay(dt);
          k = -4;
        }
        mos(10 * spr, -3 * spl);
        //mov = 2;
      }
      else if (bin == 32) {
        if (k > -5) {
          motorSpeedL(10 * spr, 10 * spl);
          delay(dt);
          k = -5;
        }
        mos(10 * spr, -5 * spl);
        mov = 2;
      }
    }//...........................................................................end sum 1

    //...............................................................................sum=3||sum=4||sum=5
    else if (sum == 3 || sum == 4 || sum == 5) {
      tcount = 0;
      if (bin == 11 || bin == 13 || bin == 9 || bin == 25 || bin == 19) {
        k30 = 1;
        mov = 1;
      }

      else if ( bin == 52 || bin == 44 || bin == 36 || bin == 38 || bin == 50) {
        k30 = 2;
        mov = 2;
      }

      else if (bin == 7 || bin == 15 || bin == 31) { //31 mane 011111
        k90 = 1;
        mov = 1;
        //        m81 = m82 = millis();
        //        while (sum != 6 && sum != 0) {
        //          check();
        //          m82 = millis();
        //          if (m82 - m81 >= 120) {
        //            break;
        //          }
        //        }
      }
      else if (bin == 56 || bin == 60 || bin == 62) {   //62 mane 111110
        k90 = 2;
        mov = 2;
        m81 = m82 = millis();
        while (sum != 6 && sum != 0) {
          check();
          m82 = millis();
          if (m82 - m81 >= 50) {
            cross = 2;
            break;
          }
        }
      }
      //...............................................................................line changing
      mi1 = millis ();
    }
    //................................................................end of sum=4

    //...........................................................................sum=6
    else if (sum == 6 && mode == 1) {
      digitalWrite(d30, HIGH);
      digitalWrite(d90, HIGH);
      k30 = 0;
      mov = 2;
      k90 = 2;
      m81 = m82 = millis();
      while (sum != 0) {
        check();
        m82 = millis();
        if (m82 - m81 >= 50) {
          if (sum == 6 && mode == 1 && counter != 0) {
            braking_mechanism();
            motorSpeedS();
            while (sum == 6) {
              check();
              if (digitalRead(calin) == HIGH) break;
            }
            text_line_follow();
            break;
          }
          else {
            cross = 2;
            mov = 0;
            break;
          }
        }
      }
      digitalWrite(d30, LOW);
      digitalWrite(d90, LOW);
      mi1 = millis();
    }


    mi2 = millis();
    if (mi2 - mi1 >= 1000)  mov = 0; //500ms por movement automatic 0 korar command

  }//end of while loop!!!!!
}//line following function
