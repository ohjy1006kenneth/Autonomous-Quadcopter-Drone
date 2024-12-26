#ifndef RF_MASTER_H
#define RF_MASTER_H

#include <Arduino.h>
#include <RF24.h>
#include <SPI.h>
#include <nRF24L01.h>
#include "main.h"

#define CE_PIN 9
#define CSN_PIN 10


/**
 * @brief Set the up radio master object
 *
 */
void setup_radio_master();

/**
 * @brief Send command data to slave and receive ack data from slave
 *
 */
void transceive_master(Cmd_Package *cmd, Telem_Package *telem);

#endif