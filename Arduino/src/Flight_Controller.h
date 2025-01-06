#ifndef FLIGHT_CONTROLLER_H
#define FLIGHT_CONTROLLER_H


#include "RF_master.h"
#include "imu.h"
#include "main.h"

//////////////////////////////////////////////////////////////////
//////////////////////////// SETTINGS ////////////////////////////
//////////////////////////////////////////////////////////////////

// Motors (pin number)
#define MOTOR1 3
#define MOTOR2 5
#define MOTOR3 6
#define MOTOR4 9

// LED (pin number)
#define RED_LED 10
#define GREEN_LED 11

// Throttle
extern float throttle_idle; // minimum throttle needed to apply to the four motors for them all to spin up, but not provide lift (idling on the ground).
extern float throttle_governor; // governor to limit the maximum throttle. (Pilot's throttle input will be scaled based on the governor value)

// Rate of change
extern float max_rate_roll; // maximum rate of change of roll angle
extern float max_rate_pitch; // maximum rate of change of pitch angle
extern float max_rate_yaw; // maximum rate of change of yaw angle

// Desired Flight Controller Cycle Time in Hz
extern float cycle_time;

// PID gains
extern float Kp_roll;
extern float Ki_roll;
extern float Kd_roll;
extern float Kp_pitch;
extern float Ki_pitch;
extern float Kd_pitch;
extern float Kp_yaw;
extern float Ki_yaw;
extern float Kd_yaw;

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