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

bool approached_end_of_part = 0;

// variables used by PID library
double temp_speed_feedback = goal_speed_part1;
double Kp=1.0, Ki=0.5, Kd=0.00;

int PID_sample_time = 50; // Set to 105ms because writeSpeed takes 100ms
// due to the way PID_library is coded, having a sample time below 100ms could
// lead to unwanted behaviour combined with the writeSpeed delay

unsigned long last_pid_compute_time;

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
  slave_resync_procedure();
  #endif

  writeSpeed(start_PWM_speed);

  servoPID.SetOutputLimits(0.0, 4.0);

  // We're doing the following because of the way the servo_loop of the slave is made (timing)
  #if MASTER == 1
  servoPID.SetSampleTime(PID_sample_time);
  #else
  servoPID.SetSampleTime(PID_sample_time-10);
  #endif

  servoPID.SetMode(AUTOMATIC);

  delay(100);

}


void loop() {
  checkAndUpdateMicroSwitchState();

  receiveUdp(); // UDP INPUT 

  servoLoop(); //loops_slave OR loop_master

}

// ######## FONCTION MODULO FLOAT ############
float f_mod(float a, float n) {          
  return a - n * floor(a / n);
}





