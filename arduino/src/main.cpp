#include <Arduino.h>
#include "../lib/cpu/cpu.h"

void setup() {
    unsigned char ROM[] = {
            // INPUT = ITR
            0x10,
            // OTR = ACC
            0x02,
            // FINISH
            0x00
    };

    cpu c(ROM);

    c.start();
}

void loop() {
// write your code here
}