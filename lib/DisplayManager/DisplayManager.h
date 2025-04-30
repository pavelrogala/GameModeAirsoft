#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

class DisplayManager {
public:
    DisplayManager(uint8_t address = 0x27, uint8_t cols = 20, uint8_t rows = 4);

    void init();
    void clear();
    void print(const String& text, uint8_t col = 0, uint8_t row = 0);
    void printCentered(const String& text, uint8_t row = 0);
    void setBacklight(bool on);

private:
    LiquidCrystal_I2C lcd;
    uint8_t cols, rows;
};

#endif
