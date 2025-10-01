#include <Arduino.h>   // Include the Arduino core library to use Serial, delay, etc.

// Declare an integer variable named 'counter' and set its initial value to 0
int counter = 0;

void setup(){
    Serial.begin(115200);   // Initialize serial communication at a baud rate of 115200
}

void loop(){

    // Print a message to indicate the start of the while loop section
    Serial.println("This is while loop");

    // Reset the counter back to 0 before entering the while loop
    counter = 0;

    /* While Loop:
       As long as the condition (counter < 10) is true,
       the code inside the loop will keep executing repeatedly.
       Once counter reaches 10, the loop stops. */
    while(counter < 10){

        Serial.println(counter);   // Print the current value of counter to the Serial Monitor
        delay(1000);               // Wait for 1000 milliseconds (1 second)
        
        // Increase the value of counter by 1
        counter++;
    }

    // Print a message to indicate the start of the for loop section
    Serial.println("This is for loop");

    /* For Loop:
       Initialization: int i = 0 → start with i equal to 0
       Condition: i < 10 → run loop while i is less than 10
       Increment: i++ → add 1 to i after every loop iteration */
    for(int i = 0; i < 10; i++){

        Serial.println(i);   // Print the current value of i
        delay(1000);         // Wait for 1000 milliseconds (1 second)
    }
}
