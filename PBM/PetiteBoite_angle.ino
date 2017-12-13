// ANGLE MESUREMENT //
#include <ams_as5048b.h>

// ANGLE SENSOR I2C
#define U_DEG 3
AMS_AS5048B angleSensor;

void setupAngle() {    
  angleSensor.begin();  
  delay(10); 
  getFirstAngle();
}

float getFirstAngle() {
  float raw_angle_with_offset = angleSensor.angleR(U_DEG, true)-offset_angle;
  if (raw_angle_with_offset < 0)
    laps_number++;
  if (simpleCheckMicroSwitch() == LOW)
    laps_number++;
  local_angle = raw_angle_with_offset + (laps_number - 1)*360.;
  Serial.print("first angle : ");Serial.println(local_angle);
  
  old_local_angle = local_angle;
  old_raw_angle = angleSensor.angleR(U_DEG, true);
  laps_timer = sync_millis();
}

void reset_offset() {
  offset_angle = angleSensor.angleR(U_DEG, true); //-3 = SAFETY  
  Serial.print("resetOffset :");Serial.println(offset_angle); 
}

void reset_laps() {
  laps_number = 1;
  laps_timer = sync_millis();
}

void getAngle() {
  // Please note that this function has less than 1ms delay
  // RAW ANGLE
  float raw_angle = angleSensor.angleR(U_DEG, true);
  if (abs(raw_angle - old_raw_angle) < 5.) { // Avoid near 0/360
    float row_angle_with_offset = raw_angle - offset_angle;   
    if (row_angle_with_offset - old_row_angle_with_offset < -300. && sync_millis() - laps_timer > 1000) {   // Happen when sensor is near 0/360 
      laps_number ++;
      laps_timer = sync_millis();
      Serial.print("add laps :"); Serial.println(laps_number);
      }
    local_angle = row_angle_with_offset + (laps_number - 1)*360.;
    local_time = sync_millis();
    
    old_local_time = local_time;
    old_local_angle = local_angle;
    old_row_angle_with_offset = row_angle_with_offset;
  }
  else {
    Serial.print("------- ERROR RAW ANGLE MESUREMENT old_raw : ");
    Serial.print(old_raw_angle);Serial.print(" raw :");Serial.println(raw_angle);
  }
          
  old_raw_angle = raw_angle;
}

void reset_expected_angle(float reset_angle) {
  Serial.print("reset angle to : "); Serial.println(reset_angle);
  start_angle = reset_angle;
  expected_angle = reset_angle;
  millis_at_start_of_part = sync_millis();
}

void compute_expected_angle() {
  float diff_time_seconds = (sync_millis() - millis_at_start_of_part) / 1000.0;
  float raw_expected_angle = (start_angle + diff_time_seconds * goal_speed_part1);
  if (raw_expected_angle > 360)
    raw_expected_angle = 360 + start_angle + (diff_time_seconds - 360./goal_speed_part1) * goal_speed_part2;
  expected_angle = addOffsetValue(raw_expected_angle);
}

