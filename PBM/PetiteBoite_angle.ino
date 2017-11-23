// Mesure de l'angle + offset + microswitch
// Calcul des derivé
// Reception du point d'angle MASTER

#include <ams_as5048b.h>

// ANGLE SENSOR I2C
#define U_DEG 3
AMS_AS5048B angleSensor;

// MICROSWITCH
int microSwitchPin = D0;
bool microSwitchState = LOW;
bool old_microSwitchState = LOW;

float offset_angle = 0; // en lien avec EEPROM

float local_angle, old_local_angle, master_angle;
float old_speed_feedback;
float acceleration;

unsigned int master_time;

void setupAngle() {
  pinMode(microSwitchPin, INPUT);    
  angleSensor.begin();   
  getFirstAngle();
}

void getFirstAngle() { 
  microSwitchState = digitalRead(microSwitchPin); 
  old_microSwitchState = microSwitchState;
  
  angleSensor.updateMovingAvgExp();delay(100);
  angleSensor.updateMovingAvgExp();delay(100);
  angleSensor.updateMovingAvgExp();delay(1);
  
  if (microSwitchState == LOW) {
    local_angle = f_mod(angleSensor.getMovingAvgExp(U_DEG) + offset_angle + 360, 720);
    goal_speed = goal_speed_part2;
  }
  else {
    local_angle = f_mod(angleSensor.getMovingAvgExp(U_DEG) + offset_angle, 360);
    goal_speed = goal_speed_part1;
  }
  old_local_angle = local_angle;
}





void getAngles() {
//  delay(10);
//  angleSensor.updateMovingAvgExp();
//  delay(10);
//  float angle = angleSensor.getMovingAvgExp(U_DEG);

    float angle = angleSensor.angleR(U_DEG, true);
  
  local_time = sync_millis(); 
  
  // changement etat microswitch
  microSwitchState = digitalRead(microSwitchPin); 
  if (microSwitchState != old_microSwitchState) {
//    Serial.print("microswitch CHANGE, new offset : ");    
    if (microSwitchState == HIGH) { //HIGH pas appuyé
      offset_angle = 360 - angle - 3; //-3 = SAFETY
      goal_speed = goal_speed_part1;
      updateEeprom();
    }
    else {
      goal_speed = goal_speed_part2;
    }
    old_microSwitchState = microSwitchState;
  } 

  // Selon etat microswitch
  if (microSwitchState == HIGH) { // 0 - 360°, relaché
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


// ######## FONCTION MODULO FLOAT ############
float f_mod(float a, float n) {          
  return a - n * floor(a / n);
}


void receive_slave_syncPoint(char* strAddress){
  if (strcmp(strAddress,"SYNC_POINT") == 0) {
    master_time = strtoul(strtok(NULL, " "), NULL, 0);
    master_angle = strtod(strtok(NULL, " "), NULL);
    new_point = true;
  }
}
