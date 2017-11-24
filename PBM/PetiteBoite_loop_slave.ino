// Synchro du slave à chaque reception d'un point

#if MASTER == 0 //For SLAVE ONLY

float speed_step;

float was_near = false;

void servoLoop() {
  if (new_point) {
    
    getAngles();

    ///////// NEAR MASTER //////////
    if (abs(diff_angle_master()) <= 5) { // near master
//        Serial.print("near_master ");
      if (!was_near) { // pour la premiere fois ?
        writeSpeed(start_PWM_speed + diff_angle_master() * 0.1);
        was_near = true;   
      }
      else { 
        if ((diff_angle() > 0.05 && diff_angle() < 5)) { // error mesurement or near 360
//          speed_step = (diff_angle_master * 0.15) + (1.2 * diff_speed); //diff_angle_master * 0.05;
          speed_step = (diff_angle_master() * 0.2) + (1 * diff_speed());
          if (speed_step >= 0.1)
            speed_step = 0.1;
          else if (speed_step <= -0.1)
            speed_step = -0.1;         
          writeSpeed(motor_PWM_speed + speed_step);
          if (motor_PWM_speed < 0.5) { // TOO SLOW
            Serial.println("MIN ");
            writeSpeed(0.5);
          }
        }
        else
          Serial.println("ERROR MESUREMENT");
      }
    } 
    /////// FAR MASTER /////////
    else {
      Serial.print("far_master :");
      if (f_mod(diff_angle_master(), 720) < 300) { // au plus vite
        Serial.print(" go fast");
        writeSpeed(max_PWM_speed); 
      } 
      else if (f_mod(diff_angle_master(), 720) > 390){ // stop
        Serial.print(" go_slow");
        writeSpeed(0);
      }
      was_near = false;
      Serial.println();
    }


    // DEBUG
//    Serial.print(" angle ");Serial.print(local_angle);
    
//    Serial.print("angle_diff: ");Serial.print(diff_angle_master);
//    Serial.print(" angle_diff_coef: ");Serial.print(10*diff_angle_master*0.2);
//    Serial.print(" speed_diff_coef: ");Serial.print(10*diff_speed*1);
//    Serial.print(" step: ");Serial.print(speed_step);
//    Serial.print(" speed: ");Serial.print(motor_PWM_speed);
//    Serial.print(" angle: ");Serial.print(local_angle);
//    Serial.print("angle_master: ");Serial.print(master_angle);
//     Serial.print(" speed_feed ");Serial.print(speed_feedback*1000);
//     Serial.print(" master_feed ");Serial.println(master_speed_feedback*1000);
//     Serial.print(" angle_diff ");Serial.print(diff_angle);
//    Serial.print(" voltage : ");Serial.println(batteryVoltage);

    new_point = false; 
  }
}
#endif
