#include <Arduino.h>

// Run once after the program starts
void setup(){

    // Initialize Serial port with baudrate 115200
    Serial.begin(115200);

    // Print "Hello World" which can be viewed via serial monitor
    Serial.print("Hello World");
}

// Repeat continuously forever
void loop(){

    // Print "This is blank line" and move to a new line automatically
    Serial.println("This is blank line");

    // Pause the entire program for 100 milliseconds
    delay(100);
}
