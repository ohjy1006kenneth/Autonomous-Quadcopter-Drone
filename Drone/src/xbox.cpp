#include "xbox.hpp"

void xbox_read() {
    if (Serial.available() > 0) {
        // Read the incoming data as a string
        String data = Serial.readString();
        Serial.println("Received data: " + data);
    }

    delay(10);
}