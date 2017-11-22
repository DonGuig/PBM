// MOTOR SPI
#include "WEMOS_Motor.h"

Motor M1(0x30, _MOTOR_A, 15000); //PWM frequency: 15 kHz


void writeSpeed(float speed_to_write) {
//  if (speed_to_write - motor_speed != 0) {
    if (speed_to_write > max_speed)
      speed_to_write = max_speed;
    else if (speed_to_write < 0) 
      speed_to_write = 0;
    motor_speed = speed_to_write;
    if (isnan(motor_speed)) {
      Serial.println("isnan");  
      motor_speed = start_speed;
    }
    if (motor_speed == 0) 
      M1.setmotor(_STOP);
    else
      M1.setmotor(_CW, motor_speed);
//  }
}
