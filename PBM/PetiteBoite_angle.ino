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
  old_local_angle = local_angle;
}

void changeOffset() {
  //should get called when we change part
  Serial.print(offset_angle);
  offset_angle = 360 - angleSensor.angleR(U_DEG, true) - 3; //-3 = SAFETY        
}

void getAngle() {
  // Please note that this function has less than 1ms delay
  old_local_time = local_time;
  old_local_angle = local_angle;
  
  float angle = angleSensor.angleR(U_DEG, true);
  local_time = sync_millis();
  // Selon etat microswitch
  if (simpleCheckMicroSwitch() == HIGH) { // 0 - 360°, relaché
    //Serial.println("SimpleCheck HIGH");
    if (old_local_angle > 700) // Zone d'erreur, pour régler la transition 720° -> 0°
      local_angle = f_mod(angle + offset_angle + 360, 720);
    else 
      local_angle = f_mod(angle + offset_angle, 360);
  }
  else { // 361 - 720°
    //Serial.println("SimpleCheck LOW");
    if (old_local_angle < 360) // Zone d'erreur, pour régler la transition 359° -> 361°
      local_angle = angle + offset_angle;
    else 
      local_angle = f_mod(angle + offset_angle, 360) + 360;
  }
  
}


void reset_expected_angle(float input_angle) {
  Serial.print("reset angle to : "); Serial.println(input_angle);
  start_angle = input_angle;
  expected_angle = input_angle;
  millis_at_start_of_part = sync_millis();
}

void compute_expected_angle(float target_speed) {
  float diff_time_seconds = (sync_millis() - millis_at_start_of_part) / 1000.0;
  expected_angle = (start_angle + diff_time_seconds * target_speed);
  expected_angle = addOffsetValue(local_angle);
}

