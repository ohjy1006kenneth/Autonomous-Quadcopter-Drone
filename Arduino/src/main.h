#ifndef MAIN_H
#define MAIN_H

#include <Arduino.h>

/*
TODO:
Send telemetry data to GCS
Send mode data to drone
*/




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

//////////////////////////////////////////////////////////////////
//////////////////////// Global Variables ////////////////////////
//////////////////////////////////////////////////////////////////

// Command data package to send to drone (Max 32 bytes)
struct Cmd_Package {
    int throttle;
    int yaw;
    int roll;
    int pitch;
    short mode; // 1: Standby, 2: Flight, 3: Fail Save, 4: Autonomous, 5: Track Human
};

// Telemetry data package to receive from drone (Max 32 bytes)
struct Telem_Package {
    float altitude;
    float heading;
    float speed;
};

// Radio data packages
extern Cmd_Package cmd_drone;
extern Telem_Package telem_drone;
extern Cmd_Package cmd_gcs;
extern Telem_Package telem_gcs;

// Connection status
extern bool radio_connected = false;
extern bool imu_connected = false;

// Define states of the drone
enum DroneMode {
    STANDBY,
    FLIGHT,
    FAIL_SAVE,
    AUTONOMOUS,
    TRACK_HUMAN
};

#endif