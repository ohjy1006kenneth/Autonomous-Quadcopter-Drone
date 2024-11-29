#include "RF_slave.h"

RF24 radio_slave(CE_PIN, CSN_PIN);

void setup_radio_slave()
{
    radio_slave.begin();
    radio_slave.setPALevel(RF24_PA_HIGH);
    radio_slave.setDataRate(RF24_250KBPS);
    radio_slave.enableAckPayload();
    radio_slave.openReadingPipe(1, thisSlaveAddress);
    radio_slave.startListening();

    Serial.println("Radio slave setup done");
}

void transceive_slave(Cmd_Package* cmd, Telem_Package* telem)
{
    radio_slave.writeAckPayload(1, cmd, sizeof(Cmd_Package));

    if (radio_slave.available()) {
        radio_slave.read(telem, sizeof(Telem_Package));
    }
}