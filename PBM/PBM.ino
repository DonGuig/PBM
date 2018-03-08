//// SELECTION MASTER or SLAVE
#define MASTER 1
#define SerialNumber 3 //Used to make array with value for inaccuracy
/*
 * ELECTRONIC CONNECTION :
 * 
 * I2C input (sensor & motor) : SCL D1, SDA D2
 * Button input : GND, (D0 -> 10k/3.3V)
 * Battery Input : GND --> 220 Ohms --> A0 <-- 1000 Ohms <-- Battery
 * 
*/

#include <PID_v1.h>

float goal_speed_part1 = 10.05; //°.s-1  (OLD : 9.78)
float goal_speed_part2 = 11.22;

// Angle & Speed Variable
float start_PWM_speed = 2.884;
double motor_PWM_speed = start_PWM_speed; // init PWM (0-100)
float max_PWM_speed = 4.0;

float offset_angle = 0; // Depending of magnet position, stored in EEPROM

// Slave receive point from master
boolean new_point = false;
unsigned long master_time;
double master_angle;

// Global Variable of angle & timing
unsigned long local_time, old_local_time;
double local_angle, old_local_angle;
// To count 0 -> 720
int laps_number = 1;
unsigned long laps_timer;

bool approached_end_of_part = 0;

// variables used by PID library
double Kp=1.0, Ki=0.5, Kd=0.00;



int PID_sample_time = 50; // Set to 105ms because writeSpeed takes 100ms
// due to the way PID_library is coded, having a sample time below 100ms could
// lead to unwanted behaviour combined with the writeSpeed delay

unsigned long last_pid_compute_time;

// variable to compute the expected angle
double expected_angle;
unsigned long millis_at_start_of_part;
float start_angle;

// Indicates in which full 360 degrees rotation we are in
float old_raw_angle,old_row_angle_with_offset, raw_expected_angle;

// Variables for implementing playback modes
// 0 = infinite loop
// 1 = 1 loop every 5 min
// 2 = 1 loop every hour
int playback_mode = 0;
String playback_mode_char = String();
// these variables to abstract modes 1 and 2
int number_of_loops_between_pauses = 2;
int loop_count = 0;
int pause_between_loops = 300; // in seconds
unsigned int loops_before_end_of_startup_phase = 2;
bool pause = false;
unsigned long millis_at_start_of_pause = 0;
bool will_stop_at_microswitch = false; // for the slave

// For the beginning procedure (get both boxes at the start of the score)
bool slave_ready_to_begin = false;
bool slave_begin = false;

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

  configWebPage();

  setupMicroSwitch();

  setupUdp();

  //getAngle();
  //writeSpeed(start_PWM_speed);
  //delay(1000);

  
  servoPID.SetOutputLimits(0.5, 4.0);

  // We're doing the following because of the way the servo_loop of the slave is made (timing)
  #if MASTER == 1
  servoPID.SetSampleTime(PID_sample_time);
  #else
  servoPID.SetSampleTime(PID_sample_time-10);
  #endif

  // will get both boxes at the beginning of the score
  // they will then wait for each other before beginning
  // beginning_procedure(); 

#if MASTER == 0
  slave_resync_procedure();
#endif
  setupAngle();
  getAngle(); 
  reset_expected_angle(local_angle);
  servoPID.SetMode(AUTOMATIC);



  delay(100);
}


void loop() {
  checkAndUpdateMicroSwitchState();

  receiveUdp(); // UDP INPUT 

  servoLoop(); //loops_slave OR loop_master

#if MASTER == 1
  handleWebClient();
#endif

}

// ######## FONCTION MODULO FLOAT ############
float f_mod(float a, float n) {          
  return a - n * floor(a / n);
}

void set_playback_mode(int mode) {
  //should be used to set the mode
  playback_mode = mode;
  if (playback_mode == 0) {playback_mode_char = "Infinite Loop";}
  else if (playback_mode == 1) {playback_mode_char = "1 Loop Every 5min";number_of_loops_between_pauses = 1; pause_between_loops = 300;}
  else if (playback_mode == 2) {playback_mode_char = "1 Loop Every Hour";number_of_loops_between_pauses = 1; pause_between_loops = 3600;}
  else if (playback_mode == 3) {playback_mode_char = "1 Loop Every 10sec";number_of_loops_between_pauses = 1; pause_between_loops = 10;}
  else {playback_mode_char = "unknown loop mode";};
  updatePlaybackModeEeprom(); // this will only update if the mode has changed
  Serial.print("Activated loop mode : "); Serial.println(playback_mode_char);
}

