#ifndef RF_MASTER_H
#define RF_MASTER_H

#include <RF24.h>
#include <SPI.h>
#include <nRF24L01.h>

#define CE_PIN 9
#define CSN_PIN 10

const byte slaveAddress[5] = { 'R', 'x', 'A', 'A', 'A' };

// Command data package to send to drone (Max 32 bytes)
struct Cmd_Package {
    int throttle;
    int yaw;
    int roll;
    int pitch;
};

// Telemetry data package to receive from drone (Max 32 bytes)
struct Telem_Package {
    int altitude;
    int heading;
    int pitch;
    int roll;
};

/**
 * @brief Set the up radio master object
 *
 */
void setup_radio_master();

/**
 * @brief Send command data to slave and receive ack data from slave
 *
 */
void transceive_master();

#endif