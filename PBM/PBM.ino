// SELECTION MASTER or SLAVE
#define MASTER 0

/*
 * ELECTRONIC CONNECTION :
 * 
 * I2C input (sensor & motor) : SCL D1, SDA D2
 * Button input : GND, (D0 -> 10k/3.3V)
 * Battery Input : GND --> 220 Ohms --> A0 <-- 1000 Ohms <-- Battery
*/

#include <PID_v1.h>

float goal_speed_part1 = 10.05; //°.s-1  (OLD : 9.78)
float goal_speed_part2 = 11.22;

// Angle & Speed Variable
float start_PWM_speed = 2.884;
double motor_PWM_speed = start_PWM_speed; // init PWM (0-100)
float max_PWM_speed = 5;

double goal_speed = goal_speed_part1; // will get overwritten during setup

float offset_angle = 0; // Depending of magnet position, stored in EEPROM

// Slave receive point from master
boolean new_point = false;
unsigned long master_time;
double master_angle, master_speed;

// Global Variable of angle & timing
unsigned long local_time, old_local_time;
double local_angle, old_local_angle;
float old_speed_feedback;

// Global variables for measurement only
unsigned long measurement_time, old_measurement_time;
float measurement_angle, old_measurement_angle;
float measurement_speed_feedback, old_measurement_speed_feedback;
float measurement_diff_angle;
float measurement_acceleration;

// Used to have an sliding window averaging of speed_feedback values
const int speed_avg_length = 20;
float speed_fb_array[speed_avg_length];

// sliding window avergaing of output PWM command
const int PWM_avg_length = 5;
float PWM_array[PWM_avg_length];

// statistical values that get computed
float next_speed = goal_speed_part1;
float statistical_slope = 0.0; // close to acceleration, but calculated statistically

// variables used by PID library
double temp_speed_feedback = goal_speed_part1;
double Kp=1.0, Ki=0.05, Kd=0.00;
int PID_sample_time = 100;

// variable to compute the expected angle
double expected_angle;
unsigned long millis_at_start_of_part;
float start_angle;

#if MASTER == 1
PID servoPID(&local_angle, &motor_PWM_speed, &expected_angle, Kp, Ki, Kd, DIRECT);
#else
PID servoPID(&local_angle, &motor_PWM_speed, &master_angle, Kp, Ki, Kd, DIRECT);
#endif

void setup() { 
  Serial.begin(115200);

  delay(50);

  writeSpeed(0);

  Serial.println("");Serial.println("########## START Petite Boite Musique #########");

  setupWifi();
  
  setupEeprom();

  setupMicroSwitch();

  setupAngle();

  reset_expected_angle(local_angle);


//  setupOTA();

  setupUdp();

  #if MASTER == 0
  slave_ask_for_resync();
  #endif
  
  writeSpeed(start_PWM_speed);

  servoPID.SetOutputLimits(1.5, 5.0);

  servoPID.SetSampleTime(PID_sample_time);

  servoPID.SetMode(AUTOMATIC);

  delay(100);

}


void loop() {
  checkAndUpdateMicroSwitchState();
  
  receiveUdp(); // UDP INPUT 
  
//  readBattery();  // CRASH WIFI - not use

//  ota();
  
  servoLoop(); //loops_slave OR loop_master
  #if MASTER == 1
  //syncPointLoop();
  #endif

  //delay(1);
}

// ######## FONCTION MODULO FLOAT ############
float f_mod(float a, float n) {          
  return a - n * floor(a / n);
}





