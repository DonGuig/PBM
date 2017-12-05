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

void getFirstAngle() {
  
//  angleSensor.updateMovingAvgExp();delay(100);
//  angleSensor.updateMovingAvgExp();delay(100);
//  angleSensor.updateMovingAvgExp();delay(1);

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

void measureAngle() {
  // This is only used for measurement and does not use the same variables as getAngle()
  float angle = angleSensor.angleR(U_DEG, true);
  measurement_time = sync_millis();

  if (simpleCheckMicroSwitch() == HIGH) { // 0 - 360°, relaché
    if (old_measurement_angle > 700) // Zone d'erreur, pour régler la transition 720° -> 0°
      measurement_angle = f_mod(angle + offset_angle + 360, 720);
    else 
      measurement_angle = f_mod(angle + offset_angle, 360);
  }
  else { // 361 - 720°
    if (old_local_angle < 360) // Zone d'erreur, pour régler la transition 359° -> 361°
      measurement_angle = angle + offset_angle;
    else 
      measurement_angle = f_mod(angle + offset_angle, 360) + 360;
  }

  measurement_diff_angle = measurement_angle - old_measurement_angle;

  measurement_speed_feedback = 1000. * measurement_diff_angle / (measurement_time - old_measurement_time);

  measurement_acceleration = 1000. * (measurement_speed_feedback - old_measurement_speed_feedback) / (measurement_time - old_measurement_time);

  old_measurement_time = measurement_time;
  old_measurement_speed_feedback = measurement_speed_feedback;
  old_measurement_angle = measurement_angle;
}


void getAngle() {
//  delay(10);
//  angleSensor.updateMovingAvgExp();
//  delay(10);
//  float angle = angleSensor.getMovingAvgExp(U_DEG);

//  float angle = round(10*angleSensor.angleR(U_DEG, true))/10.;
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







