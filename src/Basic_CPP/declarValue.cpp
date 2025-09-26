#include <Arduino.h>

// ประกาศตัวแปร counter เป็นจำนวนเต็ม และให้ค่าเท่ากับ 0
int counter = 0;

// ประกาศตัวแปร decimal เป็นจำนวนทศนิยม และให้ค่าเท่ากับ 1.1
float decimal = 1.1;

// ประกาศตัวแปร text เป็นข้อความ และให้ค่า "Hi"
String text = "Hi";

// ประกาศตัวแปร yesNo เป็นค่าจริง/ค่าเท็จ(boolean) และให้ค่าเท็จ(false);
bool yesNo = false;


void setup(){

    Serial.begin(115200);

    // ให้ค่าตัวแปร counter เท่ากับ 2
    counter = 2;
    // String(counter) คือการแปลง counter ให้เป็น String ซึ่งส่งผลให้สามารถนำไปรวมกับข้อความก่อนหน้าแล้ว จึง print ออกมาได้
    Serial.println("counter: " + String(counter));

    // บวก 3 เข้าไปในตัวแปร counter
    counter += 3;
}

void loop(){
}
