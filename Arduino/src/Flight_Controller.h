#ifndef FLIGHT_CONTROLLER_H
#define FLIGHT_CONTROLLER_H
#include <Arduino.h>

//////////////////////////////////////////////////////////////////
//////////////////////////// SETTINGS ////////////////////////////
//////////////////////////////////////////////////////////////////

// Motors
#define MOTOR1 3
#define MOTOR2 5
#define MOTOR3 6
#define MOTOR4 9

// Throttle
float throttle_idle = 0.1; // minumum throttle needed to apply to the four motors for them all to spin up, but not provide lift (idling on the ground).
float throttle_governor = 0.8; // governor to limit the maximum throttle. (Pilot's throttle input will be scaled based on the governor value)

// Rate of change
float max_rate_roll = 10.0; // maximum rate of change of roll angle
float max_rate_pitch = 10.0; // maximum rate of change of pitch angle
float max_rate_yaw = 10.0; // maximum rate of change of yaw angle

// Desired Flight Controller Cycle Time in Hz
float cycle_time = 500.0;

// PID gains
float Kp_roll = 0.2;
float Ki_roll = 0.0;
float Kd_roll = 0.0;
float Kp_pitch = 0.2;
float Ki_pitch = 0.0;
float Kd_pitch = 0.0;
float Kp_yaw = 0.2;
float Ki_yaw = 0.0;
float Kd_yaw = 0.0;





//////////////////////////////////////////////////////////////////
/////////////////////////// FUNCTIONS ////////////////////////////
//////////////////////////////////////////////////////////////////

/**
 * @brief Function to setup flight controller
 * 
 */
void flight_controller_setup ();

/**
 * @brief Function to control the flight controller
 * 
 */
void flight_controller_loop ();

/**
 * @brief Function to setup pwm with potentiometer (for testing)
 * 
 * @param pwm pin that has PWM function
 * @param pot Analog input pin for potentiometer
 */
void pot_pwm_setup (int pwm, int pot);

/**
 * @brief Function to convert potentiometer value to pwm value (for testing)
 * 
 * @param pwm Pin that has PWM function
 * @param pot Analog input pin for potentiometer
 */
void pot_pwm_convert ();

#endif