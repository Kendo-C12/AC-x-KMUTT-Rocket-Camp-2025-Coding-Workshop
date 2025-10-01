#include <Arduino.h>

// Declare an integer variable counter and set it to 0
int counter = 0;

// Declare a function to shorten repetitive tasks
void printValue(){
    Serial.println("counter is now: " + String(counter));    
    delay(1000);
}

void setup(){
    Serial.begin(115200);
}

void loop(){

    // Set counter to 0
    counter = 0;

    /* If the condition in while is true, execute the block 
       repeatedly until it becomes false */
    while(counter < 10){

        // Call the function
        printValue();
        // Add 1 to the variable counter
        counter++;
    }
}

/* Functions must be declared before they are called; otherwise, 
   build will fail */
