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
  float goal_speed_part2 = 10.97;
#else
  float goal_speed_part1 = 10.05;
  float goal_speed_part2 = 10.97;
#endif


// Variable d'angulation / Vitesse
float start_speed = 2.884, motor_speed = start_speed; // init PWM (0-100)
float goal_speed = goal_speed_part1; 
float max_speed = 5; 

boolean new_point = false;

float diff_angle,diff_time, speed_feedback, diff_speed, diff_angle_master;

unsigned int local_time, old_local_time;

void setup() { 
  Serial.begin(115200);
  
  writeSpeed(0);
  
  Serial.println("");Serial.println("########## START Petite Boite Musique #########");

  setupEeprom();
  
  setupAngle();  

  setupWifi();

  setupOTA();
  
  #if MASTER == 0
  re_sync();
  #endif
  
  writeSpeed(start_speed);
}


void loop() {
  receiveUdp(); // UDP INPUT 
  
  readBattery();  

  ota();
  
  servoLoop(); //loops_slave OR loop_master

  delay(5);
}







