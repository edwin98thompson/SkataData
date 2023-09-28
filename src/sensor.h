#include <Arduino.h>
#include <Wire.h>
#include <MPU6050.h>


class MPU6050Sensor {
public:
    MPU6050Sensor() {}
    bool initialize() {
        Wire.begin();
        mpu.initialize();
        if (mpu.testConnection()) {
            return true;
        } else {
            return false;
        }
    }

    void readData(int16_t* ax, int16_t* ay, int16_t* az, int16_t* gx, int16_t* gy, int16_t* gz) {
        mpu.getMotion6(ax, ay, az, gx, gy, gz);
    }
    
    float convertToDegreesPerSecond(int16_t rawValue) {
        return static_cast<float>(rawValue) / 131.0;
    }

private:
    MPU6050 mpu;
};
