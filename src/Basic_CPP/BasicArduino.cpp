#include <Arduino.h>

// ทำครั้งเดี่ยวหลังจากเริ่ม run โปรแกรม
void setup(){

    // ประกาศใช้ Serial port ที่ baudrate 1152000
    Serial.begin(115200);

    // Print "Hello World" โดยที่จะเข้าดึงได้โดยใช้ serial monitor
    Serial.print("Hello World");
}

// ทำซ้ำไปเรื่อยๆ ไม่มีวันสิ้นสุด
void loop(){

    // Print "This is blank line" แล้วเว้นบรรทัดอัตโนมัติ
    Serial.println("This is blank line");

    // การขัดจังหวะโปรแกรมทั้งหมดเป็นเวลา 100 มิลลิวินาที
    delay(100);
}
