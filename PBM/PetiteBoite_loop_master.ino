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

    Serial.print(goal_speed);Serial.print(";");
    Serial.print(measurement_angle);Serial.print(";");//Serial.print(diff_angle());Serial.print(";");
    Serial.print(measurement_speed_feedback);Serial.print(";");
    Serial.print(array_average(speed_fb_array, speed_avg_length));Serial.print(";");  
    Serial.print(motor_PWM_speed);Serial.println(";");

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
  if ((sync_millis() - old_local_time) > 500) { // Servo LOOP           
    getAngle();

    enqueue_and_rotate_array(speed_fb_array, speed_avg_length, speed_feedback());

    //print_array(speed_fb_array, speed_avg_length);
    //Serial.print("Avg speed_feedback : "); Serial.println(array_average(speed_fb_array, speed_avg_length));
    
   if (diff_angle() > 0.1 && diff_angle() < 20 && abs(acceleration()) < 1.0) { // mesure error or near 360
     
    writeSpeed(motor_PWM_speed + servo_speed_step(array_average(speed_fb_array, speed_avg_length)));   
  }    

  else {
    Serial.print("MESUREMENT ERROR : ");
    //Serial.print("diff_angle ");Serial.print(diff_angle());
    //Serial.print(" acceleration ");Serial.print(acceleration());
    Serial.println();
  }  


  updateOldAngle();
  }
}

float servo_speed_step(float speed) {
  float servo_step = 0;
  if (speed < goal_speed) {
      if (speed < goal_speed * 0.90) {
        servo_step = 0.2;
      }
      else if (speed < goal_speed * 0.95) {
        servo_step = 0.1;
      }
      else if (speed < goal_speed * 0.96) {
        servo_step = 0.07;
      }
      else if (speed < goal_speed * 0.97) {
        servo_step = 0.05;
      }
      else if (speed < goal_speed * 0.98) {
        servo_step = 0.03;
      }
      else if (speed < goal_speed * 0.99) {
        servo_step = 0.02;
      }
      else
        servo_step = 0.01;
    }  
    else if (speed > goal_speed) {
      if (speed > goal_speed * 1.10) {
        servo_step = -0.2;
      }
      else if (speed > goal_speed * 1.05) {
        servo_step = -0.1;
      }
      else if (speed > goal_speed * 1.04) {
        servo_step = -0.07;
      }
      else if (speed > goal_speed * 1.03) {
        servo_step = -0.05;
      }
      else if (speed > goal_speed * 1.02) {
        servo_step = -0.03;
      }
      else if (speed > goal_speed * 1.01) {
        servo_step = -0.02;
      }
      else 
        servo_step = -0.01;
    }
    return servo_step;
}
#endif
