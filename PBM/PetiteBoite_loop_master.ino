// fonction de synchro locale + Envoi de la position au slave.
#if MASTER == 1 // UNIQUEMENT POUR LE MASTER

unsigned long old_local_time_for_udp;
unsigned long refresh_time_for_udp = 250;

void syncPointLoop(){
  if ((sync_millis() - old_local_time_for_udp) > refresh_time_for_udp) {
    measureAngle();
    send_master_sync_point(measurement_time, measurement_angle); 

    old_local_time_for_udp = sync_millis();
    
    if (local_angle < 5) {
      refresh_time_for_udp = 50;
    }
    else {
      refresh_time_for_udp = 250;
    }
      // CSV FILE, interessant pour des tableaux/courbes
//    Serial.print(local_time);Serial.print(";");Serial.print(diff_time);Serial.print(";");


    //Serial.print(goal_speed);Serial.print(";");
    //Serial.print(measurement_angle);Serial.print(";");//Serial.print(diff_angle());Serial.print(";");
    //Serial.print(1000.0 * statistical_slope);Serial.print(";");
    //Serial.print(next_speed);Serial.print(";");
    //Serial.print(next_speed);Serial.print(";");  
    //Serial.print(motor_PWM_speed);Serial.println(";");


    // DEBUG
//    Serial.print("angle "); Serial.print(local_angle);
//        Serial.print(" old_local_angle "); Serial.print(old_local_angle);
//        Serial.print(" angle_diff ");Serial.print(diff_angle());
//        Serial.print(" temps_diff ");Serial.print(diff_time);
//        Serial.print(" speed_feedback : ");Serial.print(speed_feedback());
//        Serial.print(" goal_speed ");Serial.print(goal_speed);
//        Serial.print(" acceleration ");Serial.print(abs(acceleration()));
//    Serial.print(" send speed : ");Serial.println(motor_PWM_speed);
//    Serial.print(" voltage : ");Serial.println(batteryVoltage); 
}
}


void servoLoop() {

  if ((sync_millis() - old_local_time) > 10) { // Servo LOOP           
    getAngle();

    compute_expected_angle(goal_speed);

    Serial.print(goal_speed);Serial.print(";");
    Serial.print(expected_angle - local_angle);Serial.print(";");
    Serial.print(local_angle);Serial.print(";");
    Serial.print(expected_angle);Serial.print(";");
    Serial.print(motor_PWM_speed);Serial.println(";");

    updateOldAngle();
  }
  if (servoPID.Compute()) {
    send_master_sync_point(local_time, expected_angle);

/*
    Serial.print(goal_speed);Serial.print(";");
    Serial.print(expected_angle - local_angle);Serial.print(";");
    Serial.print(local_angle);Serial.print(";");
    Serial.print(expected_angle);Serial.print(";");
    Serial.print(motor_PWM_speed);Serial.println(";");
*/  
    //Serial.print("Kp : "); Serial.println(servoPID.GetKp());
    //Serial.print("Ki : "); Serial.println(servoPID.GetKi());
    //Serial.print("Kd : "); Serial.println(servoPID.GetKd());
    //Serial.print("mode : "); Serial.println(servoPID.GetMode());

  }
  writeSpeed(motor_PWM_speed);
}

float weighted_average(float a, float b, int percentage_of_a) {
  return (((percentage_of_a * a) + ((100 - percentage_of_a) * b)) / 100);
}

float servo_speed_step() {
  float step_factor = 0.08;
  float slope_factor = 0.0;

  return (step_factor * ((goal_speed - next_speed) + slope_factor * statistical_slope));

}

#endif
