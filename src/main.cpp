#include <Arduino.h>
#include "StateMachine.h"

StateMachine stateMachine;

void setup() {
    Serial.begin(115200);
    stateMachine.begin();
}

void loop() {
    stateMachine.update();
}
