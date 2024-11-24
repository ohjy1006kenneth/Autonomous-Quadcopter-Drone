#define PROG_DRONE 1
#define PROG_GCS 2

#define PROG PROG_DRONE

#if PROG == PROG_DRONE
#include "src/RF_slave.h"
#include "src/imu.h"

bool gbSenserConnectState = false;

void setup()
{
    Serial.begin(9600);
    Serial.println("This is Drone");

    // Setup and configure rf radio
    setup_radio_slave();

    // Setup and configure imu
    IMU_EN_SENSOR_TYPE enMotionSensorType, enPressureType;

    imuInit(&enMotionSensorType, &enPressureType);
    if (IMU_EN_SENSOR_TYPE_ICM20948 == enMotionSensorType) {
        Serial.println("Motion sersor is ICM-20948");
    } else {
        Serial.println("Motion sersor NULL");
    }
    if (IMU_EN_SENSOR_TYPE_BMP280 == enPressureType) {
        Serial.println("Pressure sersor is BMP280");
    } else {
        Serial.println("Pressure sersor NULL");
    }
    delay(1000);
}

void loop()
{
    transceive_slave();
}
#endif

#if PROG == PROG_GCS
#include "src/RF_master.h"

void setup()
{
    Serial.begin(9600);
    Serial.println("This is Ground Control Station");

    // Setup and configure rf radio
    setup_radio_master();

    delay(1000);
}

void loop()
{
    transceive_master();
}

#endif