// fonction de synchro locale + Envoi de la position au slave.
#if MASTER == 1 // UNIQUEMENT POUR LE MASTER
unsigned long old_local_time_for_udp;
void syncPointLoop(){
  if ((sync_millis() - old_local_time_for_udp) > 250) {
    getAngle();
    send_master_sync_point(local_time, local_angle); 
    old_local_time_for_udp = sync_millis();
  }
}


void servoLoop() {
  if ((sync_millis() - old_local_time) > 250) { // Servo LOOP           
    getAngle();
    
   if (diff_angle() > 0.1 && diff_angle() < 10 && abs(acceleration()) < 3) { // mesure error or near 360
      
    writeSpeed(motor_PWM_speed + servo_speed_step());   
  }    

  else {
    Serial.print("MESUREMENT ERROR : ");
    Serial.print("diff_angle ");Serial.print(diff_angle());
    Serial.print(" acceleration ");Serial.print(acceleration());
    Serial.println();
  }  

// CSV FILE, interessant pour des tableaux/courbes
//    Serial.print(local_time);Serial.print(";");Serial.print(diff_time);Serial.print(";");
    Serial.print(goal_speed);Serial.print(";");
    Serial.print(local_angle);Serial.print(";");Serial.print(diff_angle());Serial.print(";");
    Serial.print(speed_feedback());Serial.print(";");
    Serial.print(motor_PWM_speed);Serial.println(";");

    // DEBUG
//    Serial.print("angle "); Serial.print(local_angle);
//        Serial.print(" old_local_angle "); Serial.print(old_local_angle);
//        Serial.print(" angle_diff ");Serial.print(diff_angle());
//        Serial.print(" temps_diff ");Serial.print(diff_time);
//        Serial.print(" speed_feedback : ");Serial.print(speed_feedback());
//        Serial.print(" goal_speed ");Serial.print(goal_speed);
//        Serial.print(" acceleration ");Serial.print(abs(acceleration()));
//    Serial.print(" send speed : ");Serial.println(motor_PWM_speed);
//    Serial.print(" voltage : ");Serial.println(batteryVoltage);
  updateOldAngle();
  }
}

float servo_speed_step() {
  float servo_step = 0;
  if (speed_feedback() < goal_speed) {
      if (speed_feedback() < goal_speed * 0.85) {
        servo_step = 0.08;
      }
      else if (speed_feedback() < goal_speed * 0.90) {
        servo_step = 0.05;
      }
      else if (speed_feedback() < goal_speed * 0.95) {
        servo_step = 0.03;
      }
      else
        servo_step = 0.01;
    }  
    else if (speed_feedback() > goal_speed) {
      if (speed_feedback() > goal_speed * 1.15) {
        servo_step = -0.08;
      }
      else if (speed_feedback() > goal_speed * 1.10) {
        servo_step = -0.05;
      }
      else if (speed_feedback() > goal_speed * 1.05) {
        servo_step = -0.03;
      }
      else 
        servo_step = -0.01;
    }
    return servo_step;
}
#endif
