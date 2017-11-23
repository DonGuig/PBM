// Mesure de l'angle + offset
// Calcul des derivé
// Reception du point d'angle MASTER

#include <ams_as5048b.h>

// ANGLE SENSOR I2C
#define U_DEG 3
AMS_AS5048B angleSensor;

float offset_angle = 0; // en lien avec EEPROM

float local_angle, old_local_angle, master_angle;
float old_speed_feedback;
float acceleration;

unsigned long master_time;

void setupAngle() {    
  angleSensor.begin();   
  getFirstAngle();
}

void getFirstAngle() {
  
//  angleSensor.updateMovingAvgExp();delay(100);
//  angleSensor.updateMovingAvgExp();delay(100);
//  angleSensor.updateMovingAvgExp();delay(1);

  if (checkMicroSwitchState() == LOW) {
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
    updateEeprom();
}


void getAngles() {
//  delay(10);
//  angleSensor.updateMovingAvgExp();
//  delay(10);
//  float angle = angleSensor.getMovingAvgExp(U_DEG);

  float angle = angleSensor.angleR(U_DEG, true);
  
  local_time = sync_millis(); 
  


  // Selon etat microswitch
  if (checkMicroSwitchState() == HIGH) { // 0 - 360°, relaché
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

  //derivé
  diff_angle = local_angle - old_local_angle; // at normal speed near 0.8
  diff_time = local_time - old_local_time;
  speed_feedback = 1000.*diff_angle / diff_time; // °.s-1
  acceleration = speed_feedback - old_speed_feedback;
  
  old_speed_feedback = speed_feedback;
  old_local_time = local_time;
  old_local_angle = local_angle;
  
#if MASTER == 0 // SLAVE
  //Calcul du point ou était le slave lorsque le master à mesuré
//  float a = (old_local_angle - local_angle)/(old_local_time - local_time);
//  float b = local_angle - a*local_time;
//  float angle_n = f_mod(a*master_time + b, 720);
  float a = (local_angle - old_local_angle)/(local_time - old_local_time);
  float b = local_angle - a*local_time;
  float local_angle_at_master_time = f_mod(a*master_time + b, 720);
  
  diff_angle_master = master_angle - local_angle_at_master_time;  
  diff_speed = 0.1 * (goal_speed - speed_feedback);
#endif
}


void receive_slave_syncPoint(char* strAddress){
  if (strcmp(strAddress,"SYNC_POINT") == 0) {
    master_time = strtoul(strtok(NULL, " "), NULL, 0);
    master_angle = strtod(strtok(NULL, " "), NULL);
    new_point = true;
  }
}
