// SELECTION MASTER or SLAVE
#define MASTER 1
/*
 * ELECTRONIC CONNECTION :
 * 
 * I2C input (sensor & motor) : SCL D1, SDA D2
 * Button input : GND, (D0 -> 10k/3.3V)
 * Battery Input : GND --> 220 Ohms --> A0 <-- 1000 Ohms <-- Battery
*/

#if (MASTER == 1)
  float goal_speed_part1 = 10.05; //°.s-1  (OLD : 9.78)
  float goal_speed_part2 = 11.22;
// If it has no use, we will need to delete the #if MASTER statement to have same values for master + slave
#else
  float goal_speed_part1 = 10.05;
  float goal_speed_part2 = 11.22;
#endif

// Angle & Speed Variable
float start_PWM_speed = 2.884, motor_PWM_speed = start_PWM_speed; // init PWM (0-100)
float max_PWM_speed = 5;

float goal_speed = goal_speed_part1; // will get overwritten during setup

float offset_angle = 0; // Depending of magnet position, stored in EEPROM

// Slave receive point from master
boolean new_point = false;
unsigned long master_time;
float master_angle, master_speed;

// Global Variable of angle & timing
unsigned long local_time, old_local_time;
float local_angle, old_local_angle;
float old_speed_feedback;

void setup() { 
  Serial.begin(115200);

  delay(50);
  
  writeSpeed(0);
  
  Serial.println("");Serial.println("########## START Petite Boite Musique #########");

  setupEeprom();
  
  setupAngle();

  setupGoalSpeed();

  setupWifi();

  setupOTA();

  setupUdp();

  #if MASTER == 0
  slave_ask_for_resync();
  #endif
  
  writeSpeed(start_PWM_speed);
}


void loop() {
  checkMicroSwitchState();
  
  receiveUdp(); // UDP INPUT 
  
  readBattery();  

  ota();
  
  servoLoop(); //loops_slave OR loop_master

  delay(5);
}

// ######## FONCTION MODULO FLOAT ############
float f_mod(float a, float n) {          
  return a - n * floor(a / n);
}





