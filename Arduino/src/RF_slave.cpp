#include "RF_slave.h"

RF24 RF_slave(SLAVE_CE, SLAVE_CSN);

bool RF_slave_init()
{
    while (!Serial)
        ;

    RF_slave.begin();
    RF_slave.setDataRate(RF24_250KBPS);
    RF_slave.openReadingPipe(1, slaveAddress);
    RF_slave.enableAckPayload();
    RF_slave.startListening();
    return true;
}