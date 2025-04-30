#ifndef BUTTON_MANAGER_H
#define BUTTON_MANAGER_H

#include <Arduino.h>

class ButtonManager {
public:
    ButtonManager(uint8_t pin, bool activeLow = true, unsigned long debounceDelay = 50);

    void update();
    bool justPressed();
    bool justReleased();
    bool isHeld();
    bool heldFor(unsigned long durationMs);

private:
    uint8_t pin;
    uint8_t activeState;
    unsigned long debounceDelay;
    unsigned long lastDebounceTime;
    unsigned long pressStartTime;
    
    bool currentStableState;
    bool lastStableState;
    bool pressedFlag;
    bool releasedFlag;
};

#endif
