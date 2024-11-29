#ifndef MAIN_H
#define MAIN_H

// Command data package to send to drone (Max 32 bytes)
struct Cmd_Package {
    int throttle;
    int yaw;
    int roll;
    int pitch;
};

// Telemetry data package to receive from drone (Max 32 bytes)
struct Telem_Package {
    float altitude;
    float heading;
    float speed;
};

#endif