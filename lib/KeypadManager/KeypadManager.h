#ifndef KEYPAD_MANAGER_H
#define KEYPAD_MANAGER_H

#include <Keypad.h>

class KeypadManager {
public:
  KeypadManager();
  void begin();
  void update();
  char getKey();
  bool isKeyPressed(char key, unsigned long durationMs);

private:
  static const byte ROWS = 4;
  static const byte COLS = 4;
  char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
  };

  byte rowPins[ROWS] = {32, 33, 27, 14};   // Digital IO capable
  byte colPins[COLS] = {16, 17, 13, 25};   // 34/35 are Input-only pins on ESP32

  Keypad keypad;

  char lastKey;
  unsigned long keyPressStartTime;
  bool keyIsBeingHeld;
  char currentKey;
};

#endif
