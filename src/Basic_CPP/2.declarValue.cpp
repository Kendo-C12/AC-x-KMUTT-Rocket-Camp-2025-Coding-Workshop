#include <Arduino.h>

// Declare an integer variable counter and set it to 0
int counter = 0;

// Declare a float variable decimal and set it to 1.1
float decimal = 1.1;

// Declare a String variable text and set it to "Hi"
String text = "Hi";

// Declare a boolean variable yesNo and set it to false
bool yesNo = false;

#define INT_MAX MAX


void setup(){

    Serial.begin(115200);

    // Set the variable counter to 2
    counter = 2;

    Serial.println("counter: " + String(counter));

    // Add 3 to the variable counter
    counter += 3;
}

void loop(){

    /* String(counter) converts counter to a String
    allowing it to be concatenated with the preceding text for printing */

    // -------- Integer Example --------
    counter = 2;
    Serial.println("counter: " + String(counter));  // print 2

    counter += 3;
    Serial.println("counter after += 3: " + String(counter));  // print 5

    counter *= 2;
    Serial.println("counter after *= 2: " + String(counter));  // print 10

    delay(1000);

    // -------- Float Example --------
    decimal = 1.1;
    Serial.println("decimal: " + String(decimal, 2));  // print with 2 decimal places

    decimal += 2.5;
    Serial.println("decimal after += 2.5: " + String(decimal, 2)); // print 3.60

    decimal *= 1.5;
    Serial.println("decimal after *= 1.5: " + String(decimal, 2)); // print 5.40

    delay(1000);

    // -------- String Example --------
    text = "Hi";
    Serial.println("text: " + text);  // "Hi"

    text += " there!";
    Serial.println("text after += : " + text);  // "Hi there!"

    text = text + " How are you?";
    Serial.println("text after concatenation: " + text);  // "Hi there! How are you?"

    delay(1000);

    // -------- Boolean Example --------
    yesNo = false;
    Serial.println("yesNo: " + String(yesNo));  // prints 0 (false)

    yesNo = true;
    Serial.println("yesNo after set to true: " + String(yesNo)); // prints 1 (true)

    yesNo = !yesNo;  // toggle
    Serial.println("yesNo after toggle: " + String(yesNo)); // prints 0 (false)

    delay(1000);
}
