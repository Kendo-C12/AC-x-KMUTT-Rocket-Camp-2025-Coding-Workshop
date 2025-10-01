#include "spark_wiring_i2c.h"
#include "spark_wiring.h"
class Accel{
public:
    bool setAddress(int jumper);
    bool update();
    int xAccel;
    int yAccel;
    int zAccel;

private:
    int address = 0x18;
    int status;
    unsigned long startTime;
    unsigned long readTimeout = 300;
    int data[6];
};