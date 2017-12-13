// ANGLE MESUREMENT
#include <ams_as5048b.h>

// ANGLE SENSOR I2C
#define U_DEG 3
AMS_AS5048B angleSensor;

void setupAngle() {    
  angleSensor.begin();   
  getFirstAngle();
}

float getFirstAngle() {
  if (simpleCheckMicroSwitch() == LOW) {
    local_angle = f_mod(angleSensor.angleR(U_DEG, true) + offset_angle + 360, 720);
  }
  else {
    local_angle = f_mod(angleSensor.angleR(U_DEG, true) + offset_angle, 360);
  }
  Serial.print("first angle : ");Serial.println(local_angle);
  old_local_angle = local_angle;
  old_raw_angle = angleSensor.angleR(U_DEG, true);
}

void reset_angles() {
  local_angle = 0;
  old_local_angle = 0;
  old_raw_angle = angleSensor.angleR(U_DEG, true);
}


void changeOffset() {
  //should get called when we change part
  Serial.println(offset_angle);
  offset_angle = 360 - angleSensor.angleR(U_DEG, true); //-3 = SAFETY      
}

void getAngle() {
  // Please note that this function has less than 1ms delay

  local_angle += added_angle();
  local_time = sync_millis();

  old_local_time = local_time;
  old_local_angle = local_angle;

}


void reset_expected_angle(float input_angle) {
  Serial.print("reset angle to : "); Serial.println(input_angle);
  start_angle = input_angle;
  expected_angle = input_angle;
  millis_at_start_of_part = sync_millis();
}

void compute_expected_angle(float target_speed) {
  float diff_time_seconds = (sync_millis() - millis_at_start_of_part) / 1000.0;
  float raw_expected_angle = (start_angle + diff_time_seconds * target_speed);
  expected_angle = addOffsetValue(raw_expected_angle);
}

float added_angle() {
  float raw_angle = angleSensor.angleR(U_DEG, true);

  float added_value;

  if (abs(raw_angle - old_raw_angle) <= 300.0) {
    if ((raw_angle - old_raw_angle) >=0) {
      added_value = f_mod(abs(raw_angle - old_raw_angle), 360);
    }
    else {
      added_value = - (f_mod(abs(raw_angle - old_raw_angle), 360));
    }
  }
  else {
    if ((raw_angle - old_raw_angle) >= 0) {
      added_value = old_raw_angle + (360 - raw_angle);
    }
    else {
      added_value = raw_angle + (360 - old_raw_angle);
    }
  }

  old_raw_angle = raw_angle;
  return added_value;
}

