#include "DisplayManager.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1  // Reset pin # (or -1 if sharing Arduino reset)

DisplayManager::DisplayManager()
    : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET) {}

bool DisplayManager::init() {
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        return false;
    }
    display.clearDisplay();
    display.display();
    return true;
}

void DisplayManager::clear() {
    display.clearDisplay();
}

void DisplayManager::print(const String& text, int x, int y, int textSize) {
    display.setTextSize(textSize);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(x, y);
    display.print(text);
}

void DisplayManager::drawCenteredText(const String& text, int y, int textSize) {
    display.setTextSize(textSize);
    display.setTextColor(SSD1306_WHITE);
    int16_t x1, y1;
    uint16_t w, h;
    display.getTextBounds(text, 0, 0, &x1, &y1, &w, &h);
    int x = (SCREEN_WIDTH - w) / 2;
    display.setCursor(x, y);
    display.print(text);
}

void DisplayManager::show() {
    display.display();
}

void DisplayManager::clearSection(int x, int y, int w, int h) {
    display.fillRect(x, y, w, h, SSD1306_BLACK);
}
