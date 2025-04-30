#include "ButtonManager.h"

ButtonManager::ButtonManager(uint8_t pin, bool activeLow, unsigned long debounceDelay)
    : pin(pin),
      activeState(activeLow ? LOW : HIGH),
      debounceDelay(debounceDelay),
      lastDebounceTime(0),
      pressStartTime(0),
      currentStableState(!activeState),
      lastStableState(!activeState),
      pressedFlag(false),
      releasedFlag(false) {
    pinMode(pin, INPUT_PULLUP);
}

void ButtonManager::update() {
    bool reading = digitalRead(pin) == activeState;

    if (reading != currentStableState) {
        if ((millis() - lastDebounceTime) > debounceDelay) {
            lastStableState = currentStableState;
            currentStableState = reading;

            if (currentStableState && !lastStableState) {
                pressedFlag = true;
                pressStartTime = millis();
            }

            if (!currentStableState && lastStableState) {
                releasedFlag = true;
            }
        }
    } else {
        lastDebounceTime = millis();
    }
}

bool ButtonManager::justPressed() {
    if (pressedFlag) {
        pressedFlag = false;
        return true;
    }
    return false;
}

bool ButtonManager::justReleased() {
    if (releasedFlag) {
        releasedFlag = false;
        return true;
    }
    return false;
}

bool ButtonManager::isHeld() {
    return currentStableState;
}

bool ButtonManager::heldFor(unsigned long durationMs) {
    return currentStableState && (millis() - pressStartTime >= durationMs);
}
