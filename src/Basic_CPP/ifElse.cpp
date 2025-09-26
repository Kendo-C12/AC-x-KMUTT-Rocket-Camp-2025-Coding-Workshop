#include <Arduino.h>

// ประกาศตัวแปร counter เป็นจำนวนเต็ม และให้ค่าเท่ากับ 0
int counter = 0;


void setup(){
    Serial.begin(115200);
}

void loop(){

    // ถ้าใน if เป็นจริงจะเข้าทำในวงเล็บของ if statement นั้นๆ แต่ถ้าไม่จะไปเช็คต่อที่ else if statement หากไม่มีหรือเป็นเท็จหมดจะเข้าไปทำในวงเล็บ else statement
    if(counter%2 == 1){
        Serial.println("Now counter is odd");
    }
    else{   
        Serial.println("Now counter is even");
    }

    // บวก 1 เข้าไปในตัวแปร counter
    counter++;
}
