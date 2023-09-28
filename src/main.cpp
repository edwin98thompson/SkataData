#include <Arduino.h>
#include <Wire.h>
#include <MPU6050.h>
#include <Adafruit_SSD1306.h>
#include "sensor.h"
#include "OledDisplay.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1    // Reset pin # (or -1 if sharing Arduino reset pin)

MPU6050Sensor mpuSensor;
OLEDDisplay oledDisplay;

float threshold = 100.0;

void setup()
{
    Serial.begin(9600);
    if (!mpuSensor.initialize())
    {
        Serial.println("MPU connection failure");
        while (1)
            ;
    }
    Serial.println("MPU connection success");

    if (!oledDisplay.initialize())
    {
        Serial.println("Oled connection failure");
        while (1)
            ;
    }
    Serial.println("OLED connection success");

    oledDisplay.idleDisplay();
    delay(5000);
}

void loop()
{
    // Read MPU6050 data
    int16_t ax, ay, az, gx, gy, gz;
    mpuSensor.readData(&ax, &ay, &az, &gx, &gy, &gz);

    // Convert gyro values to degrees per second
    float gx_deg = mpuSensor.convertToDegreesPerSecond(gx);
    float gy_deg = mpuSensor.convertToDegreesPerSecond(gy);
    float gz_deg = mpuSensor.convertToDegreesPerSecond(gz);

    oledDisplay.updateDisplay(gx_deg, gy_deg, gz_deg);

    // if (gx_deg > threshold || gy_deg > threshold || gz_deg > threshold){
    //     oledDisplay.updateDisplay(gx_deg, gy_deg, gz_deg);
    // }
    // else{
    //     oledDisplay.idleDisplay();
    // }

    delay(100); // Delay for 1 second or adjust as needed
}