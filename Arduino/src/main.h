#ifndef MAIN_H
#define MAIN_H

#include <Arduino.h>

/*
TODO:
Send telemetry data to GCS
Send mode data to drone
*/


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
inline bool radio_connected;
inline bool imu_connected;

// Define states of the drone
enum DroneMode {
    STANDBY,
    FLIGHT,
    FAIL_SAVE,
    AUTONOMOUS,
    TRACK_HUMAN
};

#endif