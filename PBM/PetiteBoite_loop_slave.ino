// Synchro du slave à chaque reception d'un point

#if MASTER == 0 //For SLAVE ONLY

void servoLoop() {
  if (new_point) {
    getAngle();


//    Serial.print(goal_speed);Serial.print(";");
    
    Serial.print(local_angle);Serial.print(";");
    Serial.print(master_angle - local_angle);Serial.print(";");
//    Serial.print(master_angle);Serial.print(";");
    Serial.print(local_time - master_time);Serial.print(";");
    Serial.print(motor_PWM_speed);Serial.println(";");

    servoPID.Compute();
/*  
    //When we're getting very close to the change of part
    //we disengage the PID control
    // This way if the master makes it to the next part before the slave, it won't impact it
    // This will get back to AUTOMATIC once the switch is triggered
    if (local_angle > 350 && local_angle <= 355) {
      if (!approached_end_of_part) {
        writeSpeed(motor_PWM_speed*(goal_speed_part2/goal_speed_part1));
        servoPID.SetMode(MANUAL);
      }
      approached_end_of_part = 1; // will get reset when microswitch triggers
    }
    if (local_angle > 710 && local_angle <= 715) {
      if (!approached_end_of_part) {
        writeSpeed(motor_PWM_speed*(goal_speed_part1/goal_speed_part2));
        servoPID.SetMode(MANUAL);
      }
      approached_end_of_part = 1;
    }
*/
    writeSpeed(motor_PWM_speed); // !! Takes about 100ms

    new_point = false; 
    updateOldAngle();
  }
}

void receive_slave_syncPoint(char* strAddress){
  if (strcmp(strAddress,"SYNC_POINT") == 0) {
    master_time = strtoul(strtok(NULL, " "), NULL, 0);
    //Serial.print(sync_millis());Serial.print(";");Serial.println(master_time);
    //Serial.println(long(sync_millis() - master_time));
    master_angle = strtod(strtok(NULL, " "), NULL);
    new_point = true;
  }
}

void receive_slave_freewheel_syncpoint(char* strAddress){
  if (strcmp(strAddress,"FREEWHEEL") == 0) {    
    master_time = strtoul(strtok(NULL, " "), NULL, 0);
    float freewheel_speed = strtoul(strtok(NULL, " "), NULL, 0);
    Serial.println("START FREEWHEEL");
    servoPID.SetMode(MANUAL);
    // WHAT IS BETTER ? Master Speed or local speed ?
    writeSpeed(freewheel_speed); 
  }
}

void receive_slave_end_freewheel(char* strAddress){
  if (strcmp(strAddress,"END_FREEWHEEL") == 0) {
    Serial.println("END FREEWHEEL");
    getAngle();
    updateOldAngle();
    reset_expected_angle(local_angle);
    servoPID.SetMode(MANUAL);
    servoPID.SetMode(AUTOMATIC);
  }
}

#endif
