// fonction de synchro locale + Envoi de la position au slave.
#if MASTER == 1 // UNIQUEMENT POUR LE MASTER

void servoLoop() {
  if ((sync_millis() - old_local_time) > 150) { // boucle de temporisation principale            
    getAngles();
    
   if (diff_angle() > 0.1 && diff_angle() < 10 && abs(acceleration()) < 3) { // mesure error or near 360
    sendUdp("SYNC_POINT " + String(local_time) + " " + String(local_angle));   
    
    
    if (speed_feedback() < goal_speed) {
      if (speed_feedback() < goal_speed * 0.85) {
        writeSpeed(motor_PWM_speed + 0.1);
      }
      else if (speed_feedback() < goal_speed * 0.90) {
        writeSpeed(motor_PWM_speed + 0.075);
      }
      else if (speed_feedback() < goal_speed * 0.95) {
        writeSpeed(motor_PWM_speed + 0.05);
      }
      else
        writeSpeed(motor_PWM_speed + 0.01);
    }  
    else if (speed_feedback() > goal_speed) {
      if (speed_feedback() > goal_speed * 1.15) {
        writeSpeed(motor_PWM_speed - 0.1);
      }
      else if (speed_feedback() > goal_speed * 1.10) {
        writeSpeed(motor_PWM_speed - 0.075);
      }
      else if (speed_feedback() > goal_speed * 1.05) {
        writeSpeed(motor_PWM_speed - 0.05);
      }
      else 
        writeSpeed(motor_PWM_speed - 0.01);
    }
  }    
  else {
    Serial.print("MESUREMENT ERROR : ");
    Serial.print("diff_angle ");Serial.print(diff_angle());
    Serial.print(" acceleration ");Serial.print(acceleration());
    Serial.println();
  }  

// CSV FILE, interessant pour des tableaux/courbes
//    Serial.print(local_time);Serial.print(";");Serial.print(diff_time);Serial.print(";");
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

#endif
