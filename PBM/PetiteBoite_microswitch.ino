// MICROSWITCH
int microSwitchPin = D0;
bool microSwitchState = LOW;
bool old_microSwitchState = LOW;

void setupMicroSwitch() {
  pinMode(microSwitchPin, INPUT);
  microSwitchState = digitalRead(microSwitchPin);
  old_microSwitchState = microSwitchState;
  if (microSwitchState == HIGH) { goal_speed = goal_speed_part1; }
  else { goal_speed = goal_speed_part2; }
}

bool simpleCheckMicroSwitch() {
  return digitalRead(microSwitchPin);
}

bool checkAndUpdateMicroSwitchState() {
	microSwitchState = digitalRead(microSwitchPin);

// HERE WE SHOULD PUT EVERYTHING THAT HAS TO HAPPEN WHEN THE MICROSWITCH CHANGES STATE !!!!
	if (microSwitchState != old_microSwitchState) {
    	Serial.println("microswitch CHANGE");   
    	if (microSwitchState == HIGH) { //we're coming back to part1

    		changeOffset();
        updateEeprom();

    		//writeSpeed(motor_PWM_speed*(goal_speed_part1/goal_speed_part2));
        //setup_array(PWM_array, PWM_avg_length, motor_PWM_speed*(goal_speed_part1/goal_speed_part2));
        /// #####################
        // The delay is there to let the motor get to speed before the next measurement
        /// #####################
        goal_speed = goal_speed_part1;

        getAngle();
        updateOldAngle();

        while (local_angle > 1) {
          getAngle();
          updateOldAngle();
          delay(1);
        }
        
        reset_expected_angle(local_angle);
    		

    		#if MASTER == 0        
      		if(!checkWifi())
      		  slave_ask_for_resync();        
      	#endif
    	}
    	else { // we're entering part2

    		//writeSpeed(motor_PWM_speed*(goal_speed_part2/goal_speed_part1));
        //setup_array(PWM_array, PWM_avg_length, motor_PWM_speed*(goal_speed_part2/goal_speed_part1));
        /// #####################
        // The delay is there to let the motor get to speed before the next measurement
        /// #####################
        goal_speed = goal_speed_part2;

        getAngle();
        updateOldAngle();
        
        while (local_angle < 361) {
          getAngle();
          updateOldAngle();
          delay(1);
        }
        reset_expected_angle(local_angle);
    	}

    // At switch change, we need the average to start fresh
    //Serial.println("about to refresh speed_fb_array");
    //print_array(speed_fb_array, speed_avg_length);

    // we signify that we got out of the "end of part" zone
    approached_end_of_part = 0;

    // we reset the PID
    servoPID.SetMode(MANUAL);
    servoPID.SetMode(AUTOMATIC);

    old_microSwitchState = microSwitchState;

    // we refresh the measurements for them to make sense next time they get called
    getAngle();
    updateOldAngle();
	}
  return microSwitchState;
}
