#include <Arduino.h>

// Declare a 32-bit unsigned integer variable timeCounter
uint32_t timeCounter;

void setup(){
    Serial.begin(115200);

    /* Set timeCounter to the current time. millis() is the 
       Arduino board'stimer in milliseconds. It resets when 
       the board is powered on or reset, and will overflow 
       back to 0 after approximately 49.7 days. */
    timeCounter = millis();
}

void loop(){
    // Execute this block every 5 seconds
    if(millis() - timeCounter > 5000) {
        Serial.println("Now 5 second pass");
        timeCounter = millis();
    }

    Serial.println("This is one second");
    delay(1000);
}

/* timeCounter must be uint32_t because the millis() function
   returns a uint32_t. Using a smaller data type may cause overflow.

   delay does not pause the main program execution, 
   and the counting of millis() is not interrupted by delay. */
