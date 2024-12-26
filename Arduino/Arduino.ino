#define PROG_DRONE 1
#define PROG_GCS 2

#define PROG PROG_DRONE

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if PROG == PROG_DRONE
#include "src/Flight_Controller.h"

void setup() {
  flight_controller_setup();
}

void loop() {
  flight_controller_loop();
}
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if PROG == PROG_GCS
#include "src/RF_slave.h"

void setup() {
  Serial.begin(9600);
  Serial.println("This is Ground Control Station");

  // Setup and configure rf radio
  setup_radio_slave();

  delay(1000);
}

void loop() {
  // Update Ack data (Cmd data from laptop)
  if (Serial.available() > 0) {
    String temp = Serial.readStringUntil('\n');  // Read the incoming string

    // Parse the string and extract values
    int throttleIndex = temp.indexOf("Throttle: ") + 10;
    int yawIndex = temp.indexOf("Yaw: ") + 5;
    int rollIndex = temp.indexOf("Roll: ") + 6;
    int pitchIndex = temp.indexOf("Pitch: ") + 7;

    cmd_gcs.throttle = temp.substring(throttleIndex, temp.indexOf("Yaw: ", throttleIndex)).toInt();
    cmd_gcs.yaw = temp.substring(yawIndex, temp.indexOf("Roll: ", yawIndex)).toInt();
    cmd_gcs.roll = temp.substring(rollIndex, temp.indexOf("Pitch: ", rollIndex)).toInt();
    cmd_gcs.pitch = temp.substring(pitchIndex, temp.length()).toInt();
  }
  transceive_slave(&cmd_gcs, &telem_gcs);
}

#endif