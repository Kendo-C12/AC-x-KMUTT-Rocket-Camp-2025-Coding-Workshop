#include <Arduino.h>

// Declare an integer variable counter and set it to 0
int counter = 0;


void setup(){
    Serial.begin(115200);
}

void loop(){

    /* If the condition in the if statement is true, execute its block.
       Otherwise, check the else if statements if any.
       If none are true or present, execute the else block. */
    if(counter%2 == 1){
        Serial.println("Now counter is odd");
    }
    else{   
        Serial.println("Now counter is even");
    }

    // Add 1 to the variable counter
    counter++;
    delay(1000);
}
