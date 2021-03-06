//// fonction de synchro locale + Envoi de la position au slave.
#if MASTER == 1 // UNIQUEMENT POUR LE MASTER

void servoLoop() {

  if ((sync_millis() - last_pid_compute_time ) > PID_sample_time - 3) { // Servo LOOP
    //NOTE : we only update the angle measurement if we're 3ms from PID computing

    getAngle();
    compute_expected_angle();
  }

    //When we're getting very close to the change of part
    //we disengage the PID control
    // This way if the master makes it to the next part before the slave, it won't impact it
    // This will get back to AUTOMATIC once the switch is triggered
/*
    if (local_angle > 350 && local_angle <= 355) {
      if (!approached_end_of_part) {
        send_master_freewheel(local_time,motor_PWM_speed*(goal_speed_part2/goal_speed_part1));
        writeSpeed(motor_PWM_speed*(goal_speed_part2/goal_speed_part1));
        servoPID.SetMode(MANUAL);
      }
      approached_end_of_part = 1; // will get reset when microswitch triggers
    }
*/
    if (local_angle > 715 && local_angle <= 720) {
      if (!approached_end_of_part) {
        send_master_freewheel(local_time,motor_PWM_speed*(goal_speed_part2/goal_speed_part1));
        writeSpeed(motor_PWM_speed*(goal_speed_part1/goal_speed_part2));
        servoPID.SetMode(MANUAL);
      }
      approached_end_of_part = 1;
    }


  if (servoPID.Compute()) { // the .Compute takes less than 1ms
    last_pid_compute_time = sync_millis();

    send_master_sync_point(local_time, raw_expected_angle);

    writeSpeed(motor_PWM_speed);// !! 10ms delay with modified library

//    Serial.print(goal_speed);Serial.print(";");
/*
    Serial.print(expected_angle - local_angle);Serial.print(";");
    Serial.print(raw_expected_angle);Serial.print(";");
    Serial.print(local_angle);Serial.print(";");
    

    Serial.print(expected_angle);Serial.print(";");
    Serial.print(motor_PWM_speed);Serial.println(";");
*/
  }
}

float weighted_average(float a, float b, int percentage_of_a) {
  return (((percentage_of_a * a) + ((100 - percentage_of_a) * b)) / 100);
}

void send_master_sync_point(unsigned long loc_time, float loc_angle) {
  sendUdp("SYNC_POINT " + String(loc_time) + " " + String(loc_angle));
}

void send_master_freewheel(unsigned long loc_time, float freewheel_speed) {
  Serial.println("START_FREEWHEEL");
#ifdef DEBUG
      debugI("START_FREEWHEEL");
#endif
  sendUdp("FREEWHEEL " + String(loc_time) + " " + String(freewheel_speed));
}

void send_master_end_freewheel() {
  Serial.println("END MASTER FREEWHEEL");
#ifdef DEBUG
      debugI("END MASTER FREEWHEEL");
#endif
  sendUdp("END_FREEWHEEL");
}

void send_master_stop_next_loop() {
  Serial.println("sending STOP_NEXT_LOOP");
#ifdef DEBUG
      debugI("sending STOP_NEXT_LOOP");
#endif
  sendUdp("STOP_NEXT_LOOP");
}

void send_master_play() {
  Serial.println("sending PLAY");
#ifdef DEBUG
      debugI("sending PLAY");
#endif
  sendUdp("PLAY");
}

void send_master_isAlive() {
  Serial.println("sending ISALIVE");
#ifdef DEBUG
      debugI("sending ISALIVE");
#endif
  sendUdp("ISALIVE");
}

void send_master_begin() { // first play after the unit got turned on
  Serial.println("sending BEGIN");
#ifdef DEBUG
      debugI("sending BEGIN");
#endif
  sendUdp("BEGIN");
}

void receive_master_ready_to_begin(char* strAddress) {
  if (strcmp(strAddress,"READY_TO_BEGIN") == 0) {
    Serial.println("Slave ready to begin");
#ifdef DEBUG
      debugI("Slave ready to begin");
#endif
    slave_ready_to_begin = true;
  }
}
#endif
