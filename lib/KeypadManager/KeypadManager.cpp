#include "KeypadManager.h"

KeypadManager::KeypadManager()
  : keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS),
    currentKey(NO_KEY),
    lastKey(NO_KEY),
    keyPressStartTime(0),
    keyIsBeingHeld(false) {}

void KeypadManager::begin() {
  // Nothing needed
}

void KeypadManager::update() {
  currentKey = keypad.getKey();  // Cache it once per loop
}

char KeypadManager::getKey() {
  return currentKey;
}

bool KeypadManager::isKeyPressed(char key, unsigned long durationMs) {
  if (currentKey == key) {
    if (lastKey != key) {
      keyPressStartTime = millis();
      keyIsBeingHeld = false;
      lastKey = key;
    } else {
      if (!keyIsBeingHeld && millis() - keyPressStartTime >= durationMs) {
        keyIsBeingHeld = true;
        return true;
      }
    }
  } else {
    if (lastKey == key) {
      lastKey = NO_KEY;
    }
    keyPressStartTime = 0;
    keyIsBeingHeld = false;
  }

  return false;
}
