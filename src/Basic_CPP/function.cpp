#include <Arduino.h>

// ประกาศตัวแปร counter เป็นจำนวนเต็ม และให้ค่าเท่ากับ 0
int counter = 0;

// ประกาศฟังก์ชั่น เพื่อย่อสิ่งทีี่ต้องทำซ้ำๆให้สั้นลง
void printValue(){
    Serial.println("counter is now: " + String(counter));    
    delay(1000);
}

void setup(){
    Serial.begin(115200);
}

void loop(){

    // ให้ counter เท่ากับ 0
    counter = 0;

    // หากเงื่อนไขใน while เป็นจริงจะเข้าไปทำในวงเล็บเรื่อยๆจนกว่าจะเป็นเท็จ
    while(counter < 10){

        // เรีัยกใช้ฟังก์ชั่น
        printValue();
        // บวก 1 เข้าไปในตัวแปร counter
        counter++;
    }

}

// การประกาศฟังก์ชั่นต้องประกาศก่อนที่จะเรียกใช้ฟังก์ชั่นเท่านั้น มิฉะนั้นจะ build fail