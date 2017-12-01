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

bool checkMicroSwitchState() {
	microSwitchState = digitalRead(microSwitchPin);

// HERE WE SHOULD PUT EVERYTHING THAT HAS TO HAPPEN WHEN THE MICROSWITCH CHANGES STATE !!!!
	if (microSwitchState != old_microSwitchState) {
    	Serial.println("microswitch CHANGE");   
    	if (microSwitchState == HIGH) { //we're coming back to part1
      		//Serial.println("New offset_angle ");
    		changeOffset();
        updateEeprom();

    		writeSpeed(motor_PWM_speed*(goal_speed_part1/goal_speed_part2));
        /// #####################
        // The delay is there to let the motor get to speed before the next measurement
        /// #####################
        delay(500);
    		goal_speed = goal_speed_part1;

    		#if MASTER == 0        
      		if(!checkWifi())
      		  slave_ask_for_resync();        
      	#endif
    	}
    	else { // we're entering part2
    		writeSpeed(motor_PWM_speed*(goal_speed_part2/goal_speed_part1));
        /// #####################
        // The delay is there to let the motor get to speed before the next measurement
        /// #####################
        delay(500);
    		goal_speed = goal_speed_part2;
    	}
      
  // At switch change, we need the average to start fresh
    setup_speed_array(speed_fb_array, speed_avg_length, goal_speed);

    old_microSwitchState = microSwitchState;
	}
  return microSwitchState;
}
