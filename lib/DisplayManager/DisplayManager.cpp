#include "DisplayManager.h"

// Define the display width and height
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// Define the custom pins
#define OLED_DC_PIN   -1   // Data/Command pin
#define OLED_CS_PIN   -1  // Chip Select pin
#define OLED_RST_PIN  -1  // No Reset pin (set to -1 if your display doesn't have one)


DisplayManager::DisplayManager()
    : display(SCREEN_WIDTH, SCREEN_HEIGHT, &SPI, OLED_DC_PIN, OLED_RST_PIN, OLED_CS_PIN) {}

bool DisplayManager::init() {
    SPI.begin(22,-1,21,-1);
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

void DisplayManager::line(int x0, int y0, int x1, int y1) {
    display.drawLine(x0, y0, x1, y1, SSD1306_WHITE);
}
