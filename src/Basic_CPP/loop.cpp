#include <Arduino.h>

// ประกาศตัวแปร counter เป็นจำนวนเต็ม และให้ค่าเท่ากับ 0
int counter = 0;


void setup(){
    Serial.begin(115200);
}

void loop(){

    // ให้ counter เท่ากับ 0
    counter = 0;

    // หากเงื่อนไขใน while เป็นจริงจะเข้าไปทำในวงเล็บเรื่อยๆจนกว่าจะเป็นเท็จ
    while(counter < 10){

        Serial.println(counter);
        delay(1000);
        // บวก 1 เข้าไปในตัวแปร counter
        counter++;
    }

}
