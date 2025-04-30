#include "DisplayManager.h"

DisplayManager::DisplayManager(uint8_t address, uint8_t cols, uint8_t rows)
    : lcd(address, cols, rows), cols(cols), rows(rows) {}

void DisplayManager::init() {
    lcd.init();
    lcd.backlight();
    lcd.clear();
}

void DisplayManager::clear() {
    lcd.clear();
}

void DisplayManager::print(const String& text, uint8_t col, uint8_t row) {
    lcd.setCursor(col, row);
    lcd.print(text);
}

void DisplayManager::printCentered(const String& text, uint8_t row) {
    int padding = max((int)(cols - text.length()) / 2, 0);
    lcd.setCursor(padding, row);
    lcd.print(text);
}

void DisplayManager::setBacklight(bool on) {
    if (on) lcd.backlight();
    else lcd.noBacklight();
}
