#include "RF_slave.h"

RF24 radio_slave(CE_PIN, CSN_PIN);

Cmd_Package cmd_rx;
Telem_Package telem_rx;

void setup_radio_slave()
{
    radio_slave.begin();
    radio_slave.setPALevel(RF24_PA_HIGH);
    radio_slave.setDataRate(RF24_250KBPS);
    radio_slave.enableAckPayload();
    radio_slave.openReadingPipe(1, thisSlaveAddress);
    radio_slave.startListening();
    radio_slave.writeAckPayload(1, &telem_rx, sizeof(Telem_Package));

    Serial.println("Radio slave setup done");
}

void transceive_slave()
{
    if (radio_slave.available()) {
        radio_slave.read(&cmd_rx, sizeof(Cmd_Package));

        // Update ack data with Imu

        telem_rx.altitude = 1;
        telem_rx.heading = 2;
        telem_rx.pitch = 3;
        telem_rx.roll = 4;

        radio_slave.writeAckPayload(1, &telem_rx, sizeof(Telem_Package));
    }
}