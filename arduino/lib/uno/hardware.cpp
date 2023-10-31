#include "hardware.h"
#include "Arduino.h"

hardware::hardware(){};

void hardware::initialize(){
    Serial.begin(9600);

    pinMode(SH, OUTPUT);
    pinMode(CLK, OUTPUT);
    pinMode(DATA, INPUT);
    pinMode(CLK_INH, OUTPUT);
    pinMode(DATA2, OUTPUT);
    pinMode(SH_CP, OUTPUT);
    pinMode(ST_CP, OUTPUT);

    digitalWrite(CLK, LOW);
    digitalWrite(SH, HIGH);
    digitalWrite(ST_CP, LOW);
    digitalWrite(SH_CP, LOW);
}

unsigned char hardware::C74HC165(){
    unsigned char data = 0;

    digitalWrite(CLK_INH, HIGH);
    digitalWrite(SH, LOW);
    delayMicroseconds(2);
    digitalWrite(SH, HIGH);
    digitalWrite(CLK_INH, LOW);

    Serial.print("Binary: ");
    for(int i = 0; i < DATA_LENGTH; i++){
        Serial.print(digitalRead(DATA));
        data |= (digitalRead(DATA) << ((DATA_LENGTH - 1) - i));
        digitalWrite(CLK, HIGH);
        delayMicroseconds(2);
        digitalWrite(CLK, LOW);
    }

    digitalWrite(SH, HIGH);
    digitalWrite(SH, LOW);

    return data;
}

void hardware::C74HC595(unsigned char data){
    for(int i = 8; i >= 0; i--){
        digitalWrite(DATA2, (data & (1 << (7 - i))) ? 1 : 0);
        digitalWrite(SH_CP, HIGH);
        delayMicroseconds(2);
        digitalWrite(SH_CP, LOW);
    }
    digitalWrite(ST_CP, HIGH);
    delayMicroseconds(2);
    digitalWrite(ST_CP, LOW);
}