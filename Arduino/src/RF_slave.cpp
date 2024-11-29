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
    // Update Ack data (Cmd data from laptop)
    if (Serial.available() > 0) {
        String temp = Serial.readStringUntil('\n'); // Read the incoming string

        // Parse the string and extract values
        int throttleIndex = temp.indexOf("Throttle: ") + 10;
        int yawIndex = temp.indexOf("Yaw: ") + 5;
        int rollIndex = temp.indexOf("Roll: ") + 6;
        int pitchIndex = temp.indexOf("Pitch: ") + 7;

        cmd->throttle = temp.substring(throttleIndex, temp.indexOf("Yaw: ", throttleIndex)).toInt();
        cmd->yaw = temp.substring(yawIndex, temp.indexOf("Roll: ", yawIndex)).toInt();
        cmd->roll = temp.substring(rollIndex, temp.indexOf("Pitch: ", rollIndex)).toInt();
        cmd->pitch = temp.substring(pitchIndex, temp.length()).toInt();

        radio_slave.writeAckPayload(1, cmd, sizeof(Cmd_Package));
    }

    if (radio_slave.available()) {
        radio_slave.read(telem, sizeof(Telem_Package));

        Serial.print("Altitude: ");
        Serial.println(telem->altitude);
        Serial.print("Heading: ");
        Serial.println(telem->heading);
        Serial.print("Speed: ");
        Serial.println(telem->speed);
    }
}