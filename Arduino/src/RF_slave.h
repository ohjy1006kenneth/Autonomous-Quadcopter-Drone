#ifndef RF_SLAVE_H
#define RF_SLAVE_H

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "RF_master.h"

#define CE_PIN 9
#define CSN_PIN 10

const byte thisSlaveAddress[5] = { 'R', 'x', 'A', 'A', 'A' };

/**
 * @brief Set the up radio slave object
 *
 */
void setup_radio_slave();

/**
 * @brief Send telemetry data to master and receive cmd data from master
 *
 */
void transceive_slave();

/**
 * @brief Update telemetry package
 *
 * @param telemPackage
 */
void updateTelemPackage(Telem_Package *telemPackage);

#endif