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

        goal_speed = goal_speed_part1;

        getAngle();
        updateOldAngle();

        while (local_angle > 1) {
          getAngle();
          updateOldAngle();
          delay(10);
        }

        reset_expected_angle(local_angle);

    		#if MASTER == 0
      	checkWifi(); // this will reboot if the device disconnected
      	#endif
    	}
    	else { // we're entering part2

        goal_speed = goal_speed_part2;

        getAngle();
        updateOldAngle();
        
        while (local_angle < 361) {
          getAngle();
          updateOldAngle();
          delay(10);
        }
        reset_expected_angle(local_angle);
    	}

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
