#include "RF_master.h"

RF24 radio_master(CE_PIN, CSN_PIN);

Cmd_Package cmd_tx;
Telem_Package telem_tx;

// Get command data from laptop
bool get_cmd()
{
    if (Serial.available() > 0) {
        String temp = Serial.readStringUntil('\n'); // Read the incoming string

        // Parse the string and extract values
        int throttleIndex = temp.indexOf("Throttle: ") + 10;
        int yawIndex = temp.indexOf("Yaw: ") + 5;
        int rollIndex = temp.indexOf("Roll: ") + 6;
        int pitchIndex = temp.indexOf("Pitch: ") + 7;

        cmd_tx.throttle = temp.substring(throttleIndex, temp.indexOf("Yaw: ", throttleIndex)).toInt();
        cmd_tx.yaw = temp.substring(yawIndex, temp.indexOf("Roll: ", yawIndex)).toInt();
        cmd_tx.roll = temp.substring(rollIndex, temp.indexOf("Pitch: ", rollIndex)).toInt();
        cmd_tx.pitch = temp.substring(pitchIndex, temp.length()).toInt();

        return true;
    }

    return false;
}

void setup_radio_master()
{
    radio_master.begin();
    radio_master.setPALevel(RF24_PA_HIGH);
    radio_master.setDataRate(RF24_250KBPS);
    radio_master.enableAckPayload();
    radio_master.setRetries(5, 15); // delay, count (5 gives a 1500 µsec delay which is needed for a 32 byte ackPayload)
    radio_master.openWritingPipe(slaveAddress);

    Serial.println("Radio master setup done");
}

void transceive_master()
{
    bool rslt;
    if (get_cmd()) {

        rslt = radio_master.write(&cmd_tx, sizeof(Cmd_Package));

        if (rslt) { // Sending data was successful
            if (radio_master.isAckPayloadAvailable()) {
                radio_master.read(&telem_tx, sizeof(Telem_Package));

                Serial.println("Ack Payload Received: ");
                Serial.print("Altitude: ");
                Serial.println(telem_tx.altitude);
                Serial.print("Heading: ");
                Serial.println(telem_tx.heading);
                Serial.print("Pitch: ");
                Serial.println(telem_tx.pitch);
                Serial.print("Roll: ");
                Serial.println(telem_tx.roll);
            } else {
                Serial.println("No Ack Payload Received");
            }
        } else {
            Serial.println("Sending data failed");
        }
    }
}