#include "RF_master.h"

RF24 radio_master(CE_PIN, CSN_PIN);

void setup_radio_master()
{
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

            Serial.println("Ack Payload Received: ");
            Serial.print("Throttle: ");
            Serial.println(cmd->throttle);
            Serial.print("Yaw: ");
            Serial.println(cmd->yaw);
            Serial.print("Roll: ");
            Serial.println(cmd->roll);
            Serial.print("Pitch: ");
            Serial.println(cmd->pitch);
        }
    } else {
        Serial.println("Sending data failed");
    }
}