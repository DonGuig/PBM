// Synchro du slave à chaque reception d'un point

#if MASTER == 0 //For SLAVE ONLY

float speed_step, max_speed_step = 0.25;

float was_near = false;

void servoLoop() {
  if (new_point) {
    getAngle();

    ///////// NEAR MASTER //////////
    if (abs(diff_angle_master()) <= 5) { // near master
//        Serial.print("near_master ");
      if (!was_near) { // pour la premiere fois ?
        writeSpeed(start_PWM_speed + diff_angle_master() * 0.1);
        was_near = true;   
      }
      else { 
        if ((diff_angle() > 0.05 && diff_angle() < 5) && abs(speed_feedback()) < 20) { // error mesurement or near 360
//          speed_step = (diff_angle_master * 0.15) + (1.2 * diff_speed); //diff_angle_master * 0.05;

          if (abs(diff_angle_master()) < 1) {
            speed_step = 1 * ((1 - 0.05) * servo_speed_step() + 0.05 * diff_angle_master()); //optimal 2* + 0.2*
          }
          else 
            speed_step = (diff_angle_master() * 0.3) + 0.7*diff_speed();
            
          if (speed_step >= max_speed_step) {
            Serial.println("MAXstep");          
            speed_step = max_speed_step;
          }
          else if (speed_step <= -max_speed_step) {
            Serial.println("MINstep");
            speed_step = -max_speed_step;         
          }
          //Serial.print(speed_step);Serial.print(" ");
          //Serial.print(servo_speed_step());Serial.print(" ");
          
          writeSpeed(motor_PWM_speed + speed_step);
          if (motor_PWM_speed < 0.5) { // TOO SLOW
            Serial.println("MIN ");
            writeSpeed(0.5);
          }
        }
        else {
          Serial.print("ERROR MESUREMENT");
          Serial.print(diff_angle());
          Serial.println();
        }
      }
    } 
    /////// FAR MASTER /////////
    else {
      Serial.print("far_master :");
      Serial.print(diff_angle_master());
      if (diff_angle_master() > 0) { // au plus vite
        Serial.print(" go fast");
        writeSpeed(max_PWM_speed); 
      } 
      else { // stop
        Serial.print(" go_slow");
        writeSpeed(0);
      }
      was_near = false;
      Serial.println();
    }


    // DEBUG
//    Serial.print(" angle ");Serial.print(local_angle);
    
//    
    
//    Serial.print(" angle_diff_coef: ");Serial.print(10*diff_angle_master*0.2);
//    Serial.print(" speed_diff_coef: ");Serial.print(10*diff_speed*1);
//    Serial.print(" step: ");Serial.print(speed_step);
//    Serial.print(" speedPWM: ");Serial.print(motor_PWM_speed);
//    Serial.print(" speed_diff: ");Serial.print(diff_speed());
//    Serial.print("angle_diff: ");Serial.print(diff_angle_master());
//    Serial.print(" angle: ");Serial.print(local_angle);
//    Serial.print("angle_master: ");Serial.print(master_angle);
//     Serial.print(" speed_feed ");Serial.print(speed_feedback());
//     Serial.print(" master_feed ");Serial.println(master_speed_feedback*1000);
//     Serial.print(" angle_diff ");Serial.print(diff_angle);
//    Serial.print(" voltage : ");Serial.print(batteryVoltage);

    //Serial.print(local_angle);Serial.print(" ");
    Serial.print(diff_speed());Serial.print(" ");
//    Serial.print(speed_feedback());Serial.print(";");
    Serial.print(diff_angle_master());Serial.print(" ");
//    Serial.print(motor_PWM_speed);Serial.print(";");

    Serial.println();
    new_point = false; 
    updateOldAngle();
  }
}

float servo_speed_step() {
  float servo_step = 0;
  if (speed_feedback() < goal_speed) {
      if (speed_feedback() < goal_speed * 0.85) {
        servo_step = 0.15;
      }
      else if (speed_feedback() < goal_speed * 0.90) {
        servo_step = 0.10;
      }
      else if (speed_feedback() < goal_speed * 0.95) {
        servo_step = 0.08;
      }
      else if (speed_feedback() < goal_speed * 0.975) {
        servo_step = 0.04;
      }
      else
        servo_step = 0.02;
    }  
    else if (speed_feedback() > goal_speed) {
      if (speed_feedback() > goal_speed * 1.15) {
        servo_step = -0.15;
      }
      else if (speed_feedback() > goal_speed * 1.10) {
        servo_step = -0.10;
      }
      else if (speed_feedback() > goal_speed * 1.05) {
        servo_step = -0.08;
      }
      else if (speed_feedback() > goal_speed * 1.025) {
        servo_step = -0.04;
      }
      else 
        servo_step = -0.02;
    }
    return servo_step;
}
#endif
