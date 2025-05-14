#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class DisplayManager {
public:
    DisplayManager();
    bool init();
    void clear();
    void print(const String& text, int x = 0, int y = 0, int textSize = 1);
    void drawCenteredText(const String& text, int y = 0, int textSize = 1);
    void show();
    void clearSection(int x, int y, int w, int h);
    void line(int x0, int y0, int x1, int y1);

private:
    Adafruit_SSD1306 display;
};

#endif
