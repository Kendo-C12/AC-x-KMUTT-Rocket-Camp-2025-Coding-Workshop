#include <Arduino.h>
#include<Wire.h>
#include "SparkFun_LIS331.h"

#include "orbit_pin_def.h"

TwoWire i2c1(PIN_SDA, PIN_SCL);

// Create an instance of the accelerometer
LIS331 accelerometer;

// // Choose interface: I2C or SPI
// // For I2C: default I2C address is 0x18 (can also be 0x19 depending on SA0 pin)

// void setup() {
//   Serial.begin(115200);
//   while (!Serial);

//   // Initialize I2Ci2c1.begin();

//   // Initialize LIS331 on I2C
//   if (accelerometer.begin(i2c1, 0x18) != 0) {
//     Serial.println("LIS331 not detected. Check wiring!");
//     while (1);
//   }

//   Serial.println("LIS331DLHTR detected!");

//   // Set range: ±2g, ±4g, or ±8g
//   accelerometer.setFullScaleRange(LIS331::RANGE_2G);

//   // Set output data rate (ODR): e.g. 100 Hz
//   accelerometer.setODR(LIS331::ODR_100_HZ);
// }

// void loop() {
//   // Read accelerometer values
//   float ax = accelerometer.readFloatAccelX();
//   float ay = accelerometer.readFloatAccelY();
//   float az = accelerometer.readFloatAccelZ();

//   // Print them
//   Serial.print("X: ");
//   Serial.print(ax, 3);
//   Serial.print(" g  Y: ");
//   Serial.print(ay, 3);
//   Serial.print(" g  Z: ");
//   Serial.print(az, 3);
//   Serial.println(" g");

//   delay(500);
// }

LIS331 xl;

void setup() 
{
  // put your setup code here, to run once:
  // pinMode(9,INPUT);       // Interrupt pin input
  i2c1.begin();
  xl.setI2CAddr(0x18);    // This MUST be called BEFORE .begin() so 
                          //  .begin() can communicate with the chip
  xl.begin(LIS331::USE_I2C); // Selects the bus to be used and sets
                          //  the power up bit on the accelerometer.
                          //  Also zeroes out all accelerometer
                          //  registers that are user writable.
  // This next section configures an interrupt. It will cause pin
  //  INT1 on the accelerometer to go high when the absolute value
  //  of the reading on the Z-axis exceeds a certain level for a
  //  certain number of samples.
  xl.intSrcConfig(LIS331::INT_SRC, 1); // Select the source of the
                          //  signal which appears on pin INT1. In
                          //  this case, we want the corresponding
                          //  interrupt's status to appear. 
  xl.setIntDuration(50, 1); // Number of samples a value must meet
                          //  the interrupt condition before an
                          //  interrupt signal is issued. At the
                          //  default rate of 50Hz, this is one sec.
  xl.setIntThreshold(2, 1); // Threshold for an interrupt. This is
                          //  not actual counts, but rather, actual
                          //  counts divided by 16.
  xl.enableInterrupt(LIS331::Z_AXIS, LIS331::TRIG_ON_HIGH, 1, true);
                          // Enable the interrupt. Parameters indicate
                          //  which axis to sample, when to trigger
                          //  (in this case, when the absolute mag
                          //  of the signal exceeds the threshold),
                          //  which interrupt source we're configuring,
                          //  and whether to enable (true) or disable
                          //  (false) the interrupt.
  Serial.begin(115200);
}

void loop() 
{
  static long loopTimer = 0;
  int16_t x, y, z;
  if (millis() - loopTimer > 1000)
  {
    loopTimer = millis();
    xl.readAxes(x, y, z);  // The readAxes() function transfers the
                           //  current axis readings into the three
                           //  parameter variables passed to it.
    Serial.println(x);
    Serial.println(y);
    Serial.println(z);
    Serial.println(xl.convertToG(6,x)); // The convertToG() function
    Serial.println(xl.convertToG(6,y)); // accepts as parameters the
    Serial.println(xl.convertToG(6,z)); // raw value and the current
    Serial.println(" ");                // maximum g-rating.
  }
  // if (digitalRead(9) == HIGH)
  // {
  //   Serial.println("Interrupt");
  // }
}