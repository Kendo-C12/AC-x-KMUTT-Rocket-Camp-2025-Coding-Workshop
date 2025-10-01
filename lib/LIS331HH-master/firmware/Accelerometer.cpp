#include "Accelerometer.h"

bool Accel::setAddress(int jumper){
    if(jumper == 1){
        address = address | 1;
    }
    
    Wire.begin();
    // Start I2C Transmission
    Wire.beginTransmission(address);
    // Select control register 1
    Wire.write(0x20);
    // Enable X, Y, Z axis, power on mode, data rate selection = 50Hz
    Wire.write(0x27);
    // Stop I2C Transmission
    status = Wire.endTransmission();
    if(status != 0){
        return false;
    }

    // Start I2C Transmission
    Wire.beginTransmission(address);
    // Select control register 4
    Wire.write(0x23);
    // Set Continuos update, +/- 6g, self-test enabled
    Wire.write(0x00);
    // Stop I2C Transmission
    status = Wire.endTransmission();
    if(status != 0){
        return false;
    }
    delay(50);
    return true;
}

bool Accel::update(){
    // Wire.beginTransmission(address);
    // Wire.write(40);
    // status = Wire.endTransmission();
    // if(status != 0){
    //     return false;
    // }
    // startTime = millis();
    // Wire.requestFrom(address, 6);
    // while(Wire.available() < 6 && millis() < startTime+readTimeout);
    // if(Wire.available() < 6){
    //     return false;
    // }
    // for(int i = 0; i < 6; i++){
    //     data[i] = Wire.read();
    // }
    for (int i = 0; i < 6; i++)
    {
        // Start I2C Transmission
        Wire.beginTransmission(address);
        // Select data register
        Wire.write((40 + i));
        // Stop I2C Transmission
        Wire.endTransmission();

        // Request 1 byte of data
        Wire.requestFrom(address, 1);

        // Read 6 bytes of data
        // xAccl lsb, xAccl msb, yAccl lsb, yAccl msb, zAccl lsb, zAccl msb
        if (Wire.available() == 1)
        {
            data[i] = Wire.read();
        }
        delay(50);
    }
    
    xAccel = ((data[1] * 256) + data[0]);
    if (xAccel > 32767)
    {
        xAccel -= 65536;
    }
    yAccel = ((data[3] * 256) + data[2]);
    if (yAccel > 32767)
    {
        yAccel -= 65536;
    }
    
    zAccel = ((data[5] * 256) + data[4]);
    if (zAccel > 32767)
    {
        zAccel -= 65536;
    }
    return true;
}