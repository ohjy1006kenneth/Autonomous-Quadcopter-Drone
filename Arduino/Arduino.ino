#define PROG_DRONE 1
#define PROG_GCS 2

#define PROG PROG_GCS

#include "src/RF_master.h"
#include "src/RF_slave.h"

unsigned long currentMillis;
unsigned long prevMillis;
unsigned long txIntervalMillis = 1000; // send once per second

#if PROG == PROG_DRONE
void setup() {}

void loop() {}
#endif

#if PROG == PROG_GCS
char ackData_tx[32] = "Hello from GCS";

Tel_Package tel_data;

void setup() {
    Serial.begin(9600);
    bool rslt = RF_master_init();

    if (rslt) {
        Serial.println("Transceiver Initialized!");
    }
    else {
        Serial.println("Transceiver Failed to Initialize!");
    }
    
}

void loop() {
    if (Serial.available() > 0) {
        String data = Serial.readString();
        Serial.println("Received data: " + data);
    } else {
    }
    Serial.println("Looping...");
    //cmd_transceive(&tel_data);
    // currentMillis = millis();
    // if (currentMillis - prevMillis >= txIntervalMillis) {
    //     cmd_transceive(&tel_data);
    // }
}

#endif
