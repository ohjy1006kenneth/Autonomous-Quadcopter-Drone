#include "src/xbox.hpp"
void setup() {
  Serial.begin(115200);
  Serial.setTimeout(10);
}

void loop() {
  xbox_read();
}
