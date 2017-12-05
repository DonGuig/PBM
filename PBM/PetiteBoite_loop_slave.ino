// Synchro du slave à chaque reception d'un point

#if MASTER == 0 //For SLAVE ONLY

void servoLoop() {
  if (new_point) {
    getAngle();


    Serial.print(goal_speed);Serial.print(";");
    Serial.print(master_angle - local_angle);Serial.print(";");
    Serial.print(local_angle);Serial.print(";");
    Serial.print(master_angle);Serial.print(";");
    Serial.print(motor_PWM_speed);Serial.println(";");

    servoPID.Compute();

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

    writeSpeed(motor_PWM_speed); // !! Takes about 100ms

    new_point = false; 
    updateOldAngle();
  }
}

#endif
