#include <Arduino.h>

// ประกาศตัวแปร timeCounter เป็นจำนวนเต็มบวก 32 bit 
uint32_t timeCounter;

void setup(){
    Serial.begin(115200);

    // ให้ timeCounter เท่ากับเวลา ณ ตอนนี้ โดย  millis() คือนาฬิกาจับเวลาของบอร์ด Arduino นับเป็นมิลลิวินาที เริ่มนับใหม่เมื่อจ่ายไฟหรือ reset และจะเกิดการ Overflow และกลับไป 0 ใหม่เมื่อผ่านไป 49.7 วัน
    timeCounter = millis();
}

void loop(){
    //  จะทำในเงื่อนไขทุกๆ 5 วินาที
    if(millis() - timeCounter > 5000) {
        Serial.println("Now 5 second pass");
        timeCounter = millis();
    }

    Serial.println("This is one second");
    delay(1000);
}

// ที่ timeCounter ต้องเป็น uint32_t เพราะฟังก์ชั่น millis() return ตัวแปรชนิด uint32_t ออกมา หากใช้ตัวแปรชนิดอื่นที่รับได้น้อยกว่านี้อาจเกินการ Overflow ได้
// delay จะไม่หยุดการทำงานของโปรแกรมหลักอย่างเดี่ยว แต่การนับของ millis() จะไม่ถูกขัดขวางโดย กำสฟั