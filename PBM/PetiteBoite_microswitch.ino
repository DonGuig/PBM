// MICROSWITCH
int microSwitchPin = D0;
bool microSwitchState = LOW;
bool old_microSwitchState = LOW;

void setupMicroSwitch() {
	  pinMode(microSwitchPin, INPUT);
	  microSwitchState = digitalRead(microSwitchPin);
	  old_microSwitchState = microSwitchState;
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
    		goal_speed = goal_speed_part1;

    		#if MASTER == 0        
      		checkWifi();
          re_sync();
      	#endif
    	}
    	else { // we're entering part2
    		writeSpeed(motor_PWM_speed*(goal_speed_part2/goal_speed_part1));
    		goal_speed = goal_speed_part2;
    	}

	old_microSwitchState = microSwitchState;
	}
  return microSwitchState;
}
