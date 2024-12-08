#include "Flight_Controller.h"

void flight_controller_setup()
{

    // RF Setup
    /*
    TODO: Setup and configure rf radio
          Procede to next step if and only if the connection is established (IMPORTANT for safety)
    */

    // IMU Setup
    /*
    TODO: Setup and calibrate imu
          Procede to next step if and only if the connection is established (IMPORTANT for safety)
          Light up an green LED to indicate that the drone is ready to fly
     */
}

void flight_controller_loop()
{
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