#include "cpu/cpu.h"

int main() {
    unsigned char ROM[] = {
            // ACC = 0x10
            0x04, 0x10,
            // STACK += ACC
            0x1A,
            // ACC = 0x05
            0x04, 0x05,
            // STACK += ACC
            0x1A,
            // ACC = 0x05
            0x04, 0xFF,
            // ACC = STACK
            0x1B,
            // OTR = ACC
            0x02,
            // FINISH
            0x00
    };

    cpu c(ROM);

    c.start();

    return 0;
}
