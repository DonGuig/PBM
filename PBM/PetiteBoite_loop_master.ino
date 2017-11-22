// fonction de synchro locale + Envoi de la position au slave.

#if MASTER == 1 // UNIQUEMENT POUR LE MASTER

void servoLoop() {
  if ((sync_millis() - old_local_time) > 100) { // each 100 ms  
            
    getAngles();
    
    if (diff_angle > 0.1 && diff_angle < 2) { // mesure error or near 360
      sendUdp("SYNC_POINT " + String(local_time) + " " + String(local_angle));
      // A VERIFIER
      if (speed_feedback < goal_speed * 0.95)
        writeSpeed(motor_speed + 0.005);
      else if (speed_feedback > goal_speed * 1.05)
        writeSpeed(motor_speed - 0.005);   
    }        
      
    old_local_time = local_time;
    old_local_angle = local_angle;  

    // CSV FILE, interessant pour des tableaux/courbes
//    Serial.print(local_time);Serial.print(";");Serial.print(diff_time);Serial.print(";");
    Serial.print(local_angle);Serial.print(";");Serial.print(diff_angle);Serial.print(";");
//    Serial.print(speed_feedback);Serial.print(";");
    Serial.print(motor_speed);Serial.println(";");

    // DEBUG
//    Serial.print("angle "); Serial.print(local_angle);
//        Serial.print(" old_local_angle "); Serial.print(old_local_angle);
//        Serial.print(" angle_diff ");Serial.print(diff_angle);
//        Serial.print(" temps_diff ");Serial.print(diff_time);
//        Serial.print(" feedback speed : ");Serial.print(motor_speed_feedback);
//    Serial.print(" send speed : ");Serial.print(motor_speed);
//    Serial.print(" voltage : ");Serial.println(batteryVoltage);
  }
}

#endif
