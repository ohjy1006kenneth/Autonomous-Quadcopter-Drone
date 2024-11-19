#ifndef RF_MASTER_H
#define RF_MASTER_H

#include <RF24.h>
#include <SPI.h>
#include <nRF24L01.h>
#include "RF_slave.h"

#define MASTER_CE 2
#define MASTER_CSN 3

const byte slaveSelect[5] = { 'R', 'x', 'A', 'A', 'A' };

bool RF_master_init();

/**
 * @brief Send command data to drone and receive telemetry data from drone.
 *
 * @param tel_data Pointer to the telemetry data package.
 */
void cmd_transceive(Tel_Package* tel_data); 

#endif