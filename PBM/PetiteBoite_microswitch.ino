//// MICROSWITCH
int microSwitchPin = D0;
bool microSwitchState = LOW;
bool old_microSwitchState = LOW;

void setupMicroSwitch() {
  pinMode(microSwitchPin, INPUT);
  microSwitchState = digitalRead(microSwitchPin);
  old_microSwitchState = microSwitchState;
/*  if (microSwitchState == HIGH) { 
    goal_speed = goal_speed_part1; 
  }
  else { 
    goal_speed = goal_speed_part2; 
  }
*/
}

bool simpleCheckMicroSwitch() {
  return microSwitchState;
}

bool checkAndUpdateMicroSwitchState() {
  microSwitchState = digitalRead(microSwitchPin);

// HERE WE SHOULD PUT EVERYTHING THAT HAS TO HAPPEN WHEN THE MICROSWITCH CHANGES STATE !!!!
  if (microSwitchState != old_microSwitchState) {
      Serial.print("microswitch CHANGE @ "); Serial.println(local_angle);
      delay(5);
      microSwitchState = digitalRead(microSwitchPin);
      
      if (microSwitchState == HIGH) { //we're coming back to part1
        Serial.println("COMING_BACK_TO_1");
//        getAngle();
        //common to all modes, at all times
        reset_laps();
        reset_offset();
        updateEeprom();



       
#if MASTER == 1
        send_master_end_freewheel();
        getAngle();
        reset_expected_angle(local_angle);

        if (loops_before_end_of_startup_phase > 0) {loops_before_end_of_startup_phase--;}
        else {loops_before_end_of_startup_phase = 0;}

        if ((playback_mode == 0 || loops_before_end_of_startup_phase > 0)) {
          // we reset the PID
          servoPID.SetMode(MANUAL);
          servoPID.SetMode(AUTOMATIC);
        }
        else if (playback_mode != 0 && loops_before_end_of_startup_phase == 0) {
          loop_count++;
          if (loop_count > number_of_loops_between_pauses) {
            Serial.println("About to start the pause");
            pause = true;
            millis_at_start_of_pause = millis();
            //stop the motion
            servoPID.SetMode(MANUAL);
            writeSpeed(0);
            setMotorStandby();
            //and do nothing but check any user interaction
            unsigned long elapsed_sec_on_pause = (millis() - millis_at_start_of_pause)/1000;
            while ( elapsed_sec_on_pause < pause_between_loops) {
              handleWebClient(); 
              delay(1000);
              elapsed_sec_on_pause = (millis() - millis_at_start_of_pause)/1000;
              if (play_now == true) {
                elapsed_sec_on_pause = pause_between_loops;
                play_now = false;
              }
              send_master_isAlive();            
            }
            //re-initialize everything to start moving again
            pause = false;
            loop_count = 1;
            reset_laps();
            send_master_play();
            getAngle();
            reset_expected_angle(local_angle);
            servoPID.SetMode(AUTOMATIC);
          }
          else {
            servoPID.SetMode(MANUAL);
            servoPID.SetMode(AUTOMATIC);
          }
        }
#else
        //delay(10);
        Serial.println("End loop");
        checkWifi(); // this will reboot if the device disconnected
        if (will_stop_at_microswitch) {
          Serial.println("Stopping at microswitch");
          servoPID.SetMode(MANUAL);
          writeSpeed(0);
          setMotorStandby();
          // do nothing but wait for master to play again
          while (will_stop_at_microswitch) {
            receiveUdp(); // when "PLAY" is received, will_stop_at_microswitch gets changed to false
//            checkWifi(); // IMPORTANT if loop mode >= 5'
//            delay(10);
          }
          Serial.println("Playing at master's request");
          servoPID.SetMode(AUTOMATIC);
        }
        else {
          Serial.println("Loop waiting for master to cross 0");
          while((abs(local_angle - master_angle) > 650)) {
            writeSpeed(1.4);
            getAngle();
            receiveUdp();
            delay(5);
            servoPID.SetMode(MANUAL);
            servoPID.SetMode(AUTOMATIC);
          }
          Serial.println("Done waiting");
        }
        getAngle();



#endif
      }



      else { // we're entering part2

#if MASTER == 1
// We are going to signal the slave that at the end of this loop
// it will have to stop
        if (playback_mode !=0 && loops_before_end_of_startup_phase == 0){
          if (loop_count >= number_of_loops_between_pauses){
             send_master_stop_next_loop();
          }
        }
#endif

      }

    // we signify that we got out of the "end of part" zone
    approached_end_of_part = 0;

    old_microSwitchState = microSwitchState;

    // we refresh the measurements for them to make sense next time they get called
    getAngle();
    
  }
  return microSwitchState;
}

void beginning_procedure() {
  // the goal of this is to get both boxes at the start of the score. Than the slave
  // will wait for the master to signal the start
  Serial.println("Starting beginning_procedure");
  bool temp_microswitch_state = digitalRead(microSwitchPin);
  bool old_temp_microswitch_state = temp_microswitch_state;
  bool reached_beginning = false;
  servoPID.SetMode(MANUAL);
  writeSpeed(4.0);// we go at full speed until we reach the beginning of the score

  while(!reached_beginning) {
    delay(10);
    temp_microswitch_state = digitalRead(microSwitchPin);
    if (temp_microswitch_state != old_temp_microswitch_state) {
      if (temp_microswitch_state == HIGH) {
        // means we reached the beginning
        Serial.println("We reached the beginning");
        reset_offset();
        reached_beginning = true;
#if MASTER == 0
        send_slave_ready_to_begin();
        writeSpeed(0.0);
        while (!slave_begin) {
          delay(100);
          send_slave_ready_to_begin();
          receiveUdp();
        }
#else
        writeSpeed(0.0);
        while (!slave_ready_to_begin) {
          receiveUdp();
          delay(10);
        }
        send_master_begin();
#endif
      }
    }
    old_temp_microswitch_state = temp_microswitch_state;
  }
  Serial.println("exiting beginning_procedure");


}
