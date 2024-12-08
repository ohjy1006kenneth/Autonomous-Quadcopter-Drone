#define PROG_DRONE 1
#define PROG_GCS 2

#define PROG PROG_DRONE

#include "src/main.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if PROG == PROG_DRONE
#include "src/RF_master.h"
#include "src/imu.h"

Cmd_Package cmd_drone;
Telem_Package telem_drone;

// Sensor connection state
bool gbSenserConnectState = false;

const int pwm = 6;
const int pot = A0;

void setup()
{
    Serial.begin(9600);
    Serial.println("This is Drone");

    // Setup and configure rf radio
    setup_radio_master();

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
    // Get data from IMU
    IMU_ST_ANGLES_DATA stAngles;
    IMU_ST_SENSOR_DATA stGyroRawData;
    IMU_ST_SENSOR_DATA stAccelRawData;
    IMU_ST_SENSOR_DATA stMagnRawData;
    int32_t s32PressureVal = 0, s32TemperatureVal = 0, s32AltitudeVal = 0;

    imuDataGet(&stAngles, &stGyroRawData, &stAccelRawData, &stMagnRawData);
    pressSensorDataGet(&s32TemperatureVal, &s32PressureVal, &s32AltitudeVal);

    // Update telemetry package
    telem_drone.altitude = (float)s32AltitudeVal / 100;

    transceive_master(&cmd_drone, &telem_drone);

    delay(1000);
}
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if PROG == PROG_GCS
#include "src/RF_slave.h"

Cmd_Package cmd_gcs;
Telem_Package telem_gcs;

void setup()
{
    Serial.begin(9600);
    Serial.println("This is Ground Control Station");

    // Setup and configure rf radio
    setup_radio_slave();

    delay(1000);
}

void loop()
{
    // Update Ack data (Cmd data from laptop)
    if (Serial.available() > 0) {
        String temp = Serial.readStringUntil('\n'); // Read the incoming string

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