#include <Arduino.h>

// ประกาศตัวแปร all เป็น struct และใมีสมาชิก counter1 และ counter2 และฟังก์ชั่น sum
struct{

    int counter1 = 0;
    int counter2 = 0;

    int sum(){
        return counter1 + counter2;
    }
}all;


void setup(){

    Serial.begin(115200);

    // ให้ค่าตัวแปร counter1 ของ struct all เท่ากับ 2
    all.counter1 = 2;

    // ให้ค่าตัวแปร counter2 ของ struct all เท่ากับ 5
    all.counter1 = 5;

    // เรียกใช้ฟังก์ชั่นรวมผลกรมของ counter1 และ counter2 ของ struct all
    Serial.println("sum: " + all.sum());
}

void loop(){
}
