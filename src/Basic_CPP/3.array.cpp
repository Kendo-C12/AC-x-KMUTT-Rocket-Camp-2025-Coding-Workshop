#include <Arduino.h>

// Declare an integer array with 10 elements
int counter[10];  // Elements are counter[0] to counter[9]

void setup() {
    Serial.begin(115200); // Start serial communication

    // Initialize the array with values 0 to 9 using a for loop
    for (int i = 0; i < 10; i++) {
        counter[i] = i;  // Store the value i in counter[i]
    }

    // Print the initialized array to Serial Monitor
    Serial.println("Array contents:");
    for (int i = 0; i < 10; i++) {
        Serial.println(counter[i]); // Print each element of the array
        delay(500);
    }
}

void loop() {
    // Example: increment each element in the array every second
    Serial.println("Values in array:");

    for (int i = 0; i < 10; i++) {
        counter[i]++;                 // Increase each element by 1
        Serial.println(String(i) + " : " + String(counter[i]));   // Print updated element
        delay(500);                  // Wait 1 second
    }

    Serial.println("Plus one to each index in array");   // Print updated element
        
    delay(2000);
}
