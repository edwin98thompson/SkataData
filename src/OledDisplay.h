#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include "idle.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1    // Reset pin # (or -1 if sharing Arduino reset pin)

class OLEDDisplay
{
public:
  OLEDDisplay() {}

  bool initialize()
  {
    if (display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {
      return true;
    }
    else
    {
      return false;
    }
  }

  void updateDisplay(float gx, float gy, float gz)
  {
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.print("GX: ");
    display.println(gx);
    display.print("GY: ");
    display.println(gy);
    display.print("GZ: ");
    display.println(gz);
    display.display();
  }

  void idleDisplay()
  {
    display.clearDisplay();
    display.drawBitmap(0, 0, idle, SCREEN_WIDTH, SCREEN_HEIGHT, SSD1306_WHITE);
    display.display();
  }

private:
  Adafruit_SSD1306 display{SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET};
};
