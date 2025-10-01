// This #include statement was automatically added by the Particle IDE.
#include "Accelerometer.h"
Accel accelerometer;
int previousX;
int previousY;
int previousZ;

unsigned long lastPublish;
unsigned long publishTimeout = 10000;

int maxRange = 500;
int minRange = -500;

void setup() {
    if(accelerometer.setAddress(0)){
        Serial.println("Sensor Ready");
        if(accelerometer.update()){
            previousX = accelerometer.xAccel;
            previousY = accelerometer.yAccel;
            previousZ = accelerometer.zAccel;
        }
    }else{
        Serial.println("Sensor Offline");
    }
}

void loop() {
    if(accelerometer.update()){
        // Serial.printf("X: %i \n", accelerometer.xAccel);
        // Serial.printf("Y: %i \n", accelerometer.yAccel);
        // Serial.printf("Z: %i \n", accelerometer.zAccel);
        
        int difX = previousX - accelerometer.xAccel;
        int difY = previousY - accelerometer.yAccel;
        int difZ = previousZ - accelerometer.zAccel;
        
        if(difX > maxRange || difX < minRange || difY > maxRange || difY < minRange ||difZ > maxRange || difZ < minRange){
            Serial.println("Movement detected");
            if(millis() > lastPublish+publishTimeout){
                Particle.publish("Movement", "Moved");
                lastPublish = millis();
            }
            
            
        }
        previousX = accelerometer.xAccel;
        previousY = accelerometer.yAccel;
        previousZ = accelerometer.zAccel;
        
    }else{
        Serial.println("Sensor Did not respond");
    }
    delay(300);
}