#include "Flight_Controller.h"

DroneMode mode; // Drone Mode (STANDBY, FLIGHT, FAIL_SAVE, AUTONOMOUS, TRACK_HUMAN)

void flight_controller_setup()
{
    Serial.begin(9600);
    radio_connected = false; // Set RF connection to false
    imu_connected = false; // Set IMU connection to false

    pinMode(RED_LED, OUTPUT); // Set the RED LED pin as output
    digitalWrite(RED_LED, HIGH); // Turn on the RED LED
    pinMode(GREEN_LED, OUTPUT); // Set the GREEN LED pin as output
    digitalWrite(GREEN_LED, LOW); // Turn off the GREEN LED

    // IMU Setup
    do {
        IMU_EN_SENSOR_TYPE enMotionSensorType, enPressureType;
        imuInit(&enMotionSensorType, &enPressureType);
        if ((IMU_EN_SENSOR_TYPE_ICM20948 == enMotionSensorType) && (IMU_EN_SENSOR_TYPE_BMP280 == enPressureType)) {
            imu_connected = true;
        } else {
            imu_connected = false;
        }
    } while (imu_connected == false);
    Serial.println("IMU Connection Established");

    // Radio Setup
    do {
        // Blink the RED LED to indicate that the drone is not ready to fly
        digitalWrite(RED_LED, HIGH);
        delay(500);
        digitalWrite(RED_LED, LOW);
        delay(500);

        radio_connected = setup_radio_master();
    } while (radio_connected == false);
    Serial.println("Radio Connection Established");

    // Set initial state of the drone to STANDBY
    mode = STANDBY;

    // Set the GREEN LED to indicate that the drone is ready to fly
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(RED_LED, LOW);
}

void flight_controller_loop()
{
    switch (mode) {
        case STANDBY: // Standby Mode (The Scout Flight Controller is standing by, press a button on the remote controller to switch to flight mode)
            
            break;
        case FLIGHT:
            // Flight Mode (The Scout Flight Controller is prepared to fly.)
            break;
        case FAIL_SAVE:
            // Fail Save Mode (Enters if safety check was not met in flight mode)
            break;
        case AUTONOMOUS:
            // Autonomous Mode (Fly Autonomously)
            break;
        case TRACK_HUMAN:
            // Track Human Mode (Follow a human)
            break;

    }

    // Standy Mode (The Scout Flight Controller is standing by, awaiting further instructions)

    /*  Flight Mode (The Scout Flight Controller is prepared to fly.)
        Switched with a button on the remote controller.
        At a minimum, motors are spun up to their idle speed.
        The flight controller will receive inputs from pilot and send it to PID controller.
        Safety Check (Performs everytime when the flight controller change from standy mode to flight mode)
            1. Run only if the setup connections are established
            2. Check if the throttle is above the minimum throttle.

        If Safety Check passes, calculate adjusted throttle.
        Then error is calculated and sent to PID controller.
        Also mark end time to see if the met the target cycle time.

        If the safety check fails, move to Fail Save Mode.

        If radio or imu disconnects any time during flight mode, move to Fail Save Mode.
    */

    /*  Fail Save Mode (Enters if safety check was not met in flight mode)
        Turn the LED to red.
        Stop the motors if it is on the ground.
        If the drone is in the air, it will try to land safely.
    */

    /*  For Future:
        1. Autonomous Mode (Fly Autonomously)
        2. Track Human Mode (Follow a human)
    */
}

int output, input;

void pot_pwm_setup(int pwm, int pot)
{
    output = pwm;
    input = pot;

    pinMode(pwm, OUTPUT);
    
    pinMode(pot, INPUT);
}

void pot_pwm_convert()
{
    int value = analogRead(input);
    value = map(value, 0, 1023, 0, 255);
    analogWrite(output, value);
}