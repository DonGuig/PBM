#define MASTER 1
// version git
/* TODO
EEPROM : update si trop de difference
re_sync : demandé par le slave, à refaire toutes les X minutes ?
OTA : à tester
*/

//I2C input (sensor & motor) : SCL D1, SDA D2
//Button input : GND, (D0 -> 10k/3.3V)
//Battery Input : GND --> 220 Ohms --> A0 <-- 1000 Ohms <-- Battery


// (2*360.)/((1*60+20)) -> 2 tour en 1'20" °/sec
#if (MASTER == 1)
  float goal_speed_part1 = 10.05; //°.s-1  (OLD : 9.78)
  float goal_speed_part2 = 12.00;
// If it has no use, we will need to delete the #if MASTER statement to have same values for master + slave
#else
  float goal_speed_part1 = 10.05;
  float goal_speed_part2 = 12.00;
#endif


// Variable d'angulation / Vitesse
float start_PWM_speed = 2.884, motor_PWM_speed = start_PWM_speed; // init PWM (0-100)
float max_PWM_speed = 5;

float goal_speed = goal_speed_part1; // will get overwritten during setup


boolean new_point = false;

float diff_angle,diff_time, speed_feedback, diff_speed, diff_angle_master;

unsigned long local_time, old_local_time;

//bool microSwitchStateChange = false;

// ######## FONCTION MODULO FLOAT ############
float f_mod(float a, float n) {          
  return a - n * floor(a / n);
}



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
  re_sync();
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







