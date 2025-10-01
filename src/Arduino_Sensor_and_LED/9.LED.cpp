#include <Arduino.h> // Include the main Arduino library for core functions

// Run once after the program starts
void setup() {

    // Initialize Serial port with baudrate 115200 for debugging/printing
    Serial.begin(115200);

    // Print a message to Serial Monitor (no newline at the end)
    Serial.print("LED_BUILTIN TEST");

    // Set the built-in LED pin as OUTPUT so we can control it
    pinMode(LED_BUILTIN, OUTPUT);
}

// Repeat continuously forever
void loop() {

    // Turn the built-in LED ON
    digitalWrite(LED_BUILTIN, HIGH);

    Serial.println("HIGH");

    delay(1000);

    // Turn the built-in LED OFF
    digitalWrite(LED_BUILTIN, LOW);

    delay(1000);

    // Blink the LED rapidly 20 times using digitalToggle
    for(int i = 0; i < 20; i++) {
        digitalToggle(LED_BUILTIN); // Toggle LED state
        delay(100); // Wait 100 milliseconds between toggles
    }

    // Short pause after blinking (100 milliseconds)
    delay(100);
}
