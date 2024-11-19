#include "RF_master.h"

// TODO: Try converting to percentage inside control_publisher.py and parse into data package in this file.

bool newData = false;

struct Cmd_Package {
    byte yaw;
    byte throttle;
    byte pitch;
    byte roll;
};

Cmd_Package cmd_data;
RF24 RF_master(MASTER_CE, MASTER_CSN);

// Helper function to show the Ack Data
void showAckData() { }

// Helper function to parse string data from laptop into commadn data package
void parseCmdData(String temp, Cmd_Package& cmd_data)
{
    byte yaw, throttle, pitch, roll;
    sscanf(temp.c_str(), "%d %d %d %d", &yaw, &throttle, &pitch, &roll);
    cmd_data.yaw = yaw;
    cmd_data.throttle = throttle;
    cmd_data.pitch = pitch;
    cmd_data.roll = roll;
}

bool RF_master_init()
{
    RF_master.begin();
    RF_master.setDataRate(RF24_250KBPS);

    RF_master.enableAckPayload();

    RF_master.setRetries(5, 5);

    RF_master.openWritingPipe(slaveSelect);
    return true;
}

void cmd_transceive(Tel_Package *tel_data)
{
    newData = false;

    if (Serial.available() > 0) {
        String temp = Serial.readString();
        parseCmdData(temp, cmd_data);
    } else {
        Serial.println("No data received!");
    }
    
    Serial.println(cmd_data.yaw);


    // bool rslt;
    // rslt = RF_master.write(&cmd_data, sizeof(Cmd_Package));

    // if (rslt) {
    //     if (RF_master.isAckPayloadAvailable()) {
    //         RF_master.read(tel_data, sizeof(Tel_Package));
    //         newData = true;
    //     }
    // }
}
