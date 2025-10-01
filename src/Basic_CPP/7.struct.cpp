#include <Arduino.h>

/*
   Example: Using a struct in Arduino

   - We create an anonymous struct named "all" with two integer members:
       counter1 and counter2
   - The struct also contains three functions:
       sum()        → adds counter1 + counter2
       difference() → subtracts counter1 - counter2
       product()    → multiplies counter1 * counter2
   - In loop(), we keep updating the counters and printing results
   - This demonstrates how a struct can hold both data and functions
*/

struct {
    int counter1 = 0;
    int counter2 = 0;

    int sum() {
        return counter1 + counter2;
    }

    int difference() {
        return counter1 - counter2;
    }

    int product() {
        return counter1 * counter2;
    }
} all;

void setup() {
    Serial.begin(115200);
}

void loop() {
    // Update counters
    all.counter1++;
    all.counter2 += 2;

    // Print struct values and results of functions
    Serial.println("counter1: " + String(all.counter1));
    Serial.println("counter2: " + String(all.counter2));
    Serial.println("sum: " + String(all.sum()));
    Serial.println("difference: " + String(all.difference()));
    Serial.println("product: " + String(all.product()));
    Serial.println("---------------------");

    delay(1000); // wait 1 second before next update
}
