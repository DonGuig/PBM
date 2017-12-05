// Mesure de l'angle + offset
// Calcul des derivé
// Reception du point d'angle MASTER

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
    offset_angle = 360 - angleSensor.angleR(U_DEG, true) - 3; //-3 = SAFETY        
}

void getAngle() {
  // Please note that this function has less than 1ms delay

  float angle = angleSensor.angleR(U_DEG, true);
  local_time = sync_millis();
  
  // Selon etat microswitch
  if (simpleCheckMicroSwitch() == HIGH) { // 0 - 360°, relaché
    if (old_local_angle > 700) // Zone d'erreur, pour régler la transition 720° -> 0°
      local_angle = f_mod(angle + offset_angle + 360, 720);
    else 
      local_angle = f_mod(angle + offset_angle, 360);
  }
  else { // 361 - 720°
    if (old_local_angle < 360) // Zone d'erreur, pour régler la transition 359° -> 361°
      local_angle = angle + offset_angle;
    else 
      local_angle = f_mod(angle + offset_angle, 360) + 360;
  }
}

float diff_angle() {
  return local_angle - old_local_angle;
}

unsigned int diff_time() {
  return local_time - old_local_time;
}

float diff_speed() {
  return (goal_speed - speed_feedback());
}

float speed_feedback() { // °.s-1
  return 1000.*diff_angle() / diff_time(); 
}

float acceleration() {
  return 1000 * (speed_feedback() - old_speed_feedback)/(local_time - old_local_time);
}

void updateOldAngle() {
  old_speed_feedback = speed_feedback();
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
  expected_angle = (start_angle + diff_time_seconds * target_speed);
}

#if MASTER == 0
float diff_angle_master() {
  float a = (local_angle - old_local_angle)/(local_time - old_local_time);
  float b = local_angle - a*local_time;
  float local_angle_at_master_time = f_mod(a * master_time + b, 720);

  float diff = master_angle - local_angle_at_master_time;
  if (diff < -360) diff += 720;
  else if (diff > 360) diff -= 720;
  return diff;
}

#endif







