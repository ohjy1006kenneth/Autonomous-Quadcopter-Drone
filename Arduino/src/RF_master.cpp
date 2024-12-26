#include "RF_master.h"

const byte slaveAddress[5] = { 'R', 'x', 'A', 'A', 'A' };
RF24 radio_master(CE_PIN, CSN_PIN);

void setup_radio_master()
{
    radio_connected = false;
    radio_master.begin();
    radio_master.setPALevel(RF24_PA_HIGH);
    radio_master.setDataRate(RF24_250KBPS);
    radio_master.enableAckPayload();
    radio_master.setRetries(5, 15); // delay, count (5 gives a 1500 µsec delay which is needed for a 32 byte ackPayload)
    radio_master.openWritingPipe(slaveAddress);
}

void transceive_master(Cmd_Package* cmd, Telem_Package* telem)
{
    bool rslt;
    rslt = radio_master.write(telem, sizeof(Telem_Package));

    if (rslt) { // Sending data was successful
        if (radio_master.isAckPayloadAvailable()) {
            radio_master.read(cmd, sizeof(Cmd_Package));

            if (cmd != NULL) {
                radio_connected = true;
            } else {
                radio_connected = false;
            }
        } else {
            Serial.println("Sending data failed");
        }
    }
}