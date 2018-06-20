//// MOTOR I2C
#include "WEMOS_Motor-MOD_PBM.h"

Motor M1(0x30, _MOTOR_B, 15000); //PWM frequency: 15 kHz

//##################
// IMPORTANT : THIS FUNCTION HAS A 100MS LATENCY => USE MODIFIED LIBRARY WITH LATENCY REDUCED TO 10ms
//##################

void writeSpeed(float speed_to_write) {

//  if (speed_to_write - motor_PWM_speed != 0) {
    if (isnan(motor_PWM_speed)) {
      //Serial.println("The motor speed is not a number");  
      motor_PWM_speed = start_PWM_speed;
    }
    else if (speed_to_write > max_PWM_speed)
      motor_PWM_speed = max_PWM_speed;
    else if (speed_to_write < 0) 
      motor_PWM_speed = 0;
    else 
      motor_PWM_speed = speed_to_write;
    
    if (motor_PWM_speed == 0) 
      M1.setmotor(_STOP);
    else
      M1.setmotor(_CW, motor_PWM_speed);
}

void setMotorStandby() {
  M1.setmotor(_STANDBY);
}

