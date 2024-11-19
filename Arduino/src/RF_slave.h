#ifndef RF_SLAVE_H
#define RF_SLAVE_H

#include <RF24.h>
#include <SPI.h>
#include <nRF24L01.h>

#define SLAVE_CE 5
#define SLAVE_CSN 6

const byte slaveAddress[5] = { 'R', 'x', 'A', 'A', 'A' };

struct Tel_Package {
    byte height;
    byte acc_x;
    byte acc_y;
    byte acc_z;
};

bool RF_slave_init();

/**
 * @brief
 *
 * @param tel_data
 */
void tel_transceive(Tel_Package* tel_data);

#endif