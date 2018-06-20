//// Synchro du slave à chaque reception d'un point

#if MASTER == 0 //For SLAVE ONLY

void servoLoop() {
  if (new_point) {
    getAngle();
 /*   
    Serial.print(local_angle);Serial.print(";");
    Serial.print(master_angle - local_angle);Serial.print(";");
    Serial.print(master_angle);Serial.print(";");
    Serial.print(long(local_time - master_time));Serial.print(";");
    Serial.print(motor_PWM_speed);Serial.println(";");
*/
    servoPID.Compute();

    writeSpeed(motor_PWM_speed);

    new_point = false;     
  }
}

void receive_slave_syncPoint(char* strAddress){
  if (strcmp(strAddress,"SYNC_POINT") == 0) {
    master_time = strtoul(strtok(NULL, " "), NULL, 0);
    //Serial.print(sync_millis());Serial.print(";");Serial.println(master_time);
    //Serial.println(long(sync_millis() - master_time));
    master_angle = strtod(strtok(NULL, " "), NULL);
    master_angle = addOffsetValue(master_angle);
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
    //writeSpeed(freewheel_speed); 
  }
}

void receive_slave_end_freewheel(char* strAddress){
  if (strcmp(strAddress,"END_FREEWHEEL") == 0) {
    Serial.println("END FREEWHEEL");
    getAngle();
    
    //reset_expected_angle(local_angle);
    servoPID.SetMode(MANUAL);
    servoPID.SetMode(AUTOMATIC);
  }
}

void receive_slave_stop_next_loop(char* strAddress) {
  if (strcmp(strAddress,"STOP_NEXT_LOOP") == 0) {
    Serial.println("Master requested STOP");
    Serial.println("Will stop at NEXT microswitch");
    will_stop_at_microswitch = true;
  }
}

void receive_slave_play(char* strAddress) {
  if (strcmp(strAddress,"PLAY") == 0) {
    Serial.println("Master requested PLAY");
    will_stop_at_microswitch = false;
  }
}

void send_slave_ready_to_begin() {
  Serial.println("Sending READY_TO_BEGIN to master");
  sendUdp("READY_TO_BEGIN");
}

void receive_slave_begin(char* strAddress) { // This is when the units got turned on
  if (strcmp(strAddress,"BEGIN") == 0) {
    Serial.println("Received_order_to_begin");
    slave_begin = true;
  }
}

void receive_slave_isAlive(char* strAddress) { // do nothing
  if (strcmp(strAddress,"ISALIVE") == 0) {
    Serial.println("Received_isAlive @"+ String(millis()));
  }
}
#endif
