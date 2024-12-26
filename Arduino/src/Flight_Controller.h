#ifndef FLIGHT_CONTROLLER_H
#define FLIGHT_CONTROLLER_H

#include "main.h"
#include "RF_master.h"
#include "imu.h"



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