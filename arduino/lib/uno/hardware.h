#ifndef ARDUINO_HARDWARE_H
#define ARDUINO_HARDWARE_H

#define SH 2
#define CLK 3
#define CLK_INH 4
#define DATA 5
#define DATA_LENGTH 8
#define DATA2 8
#define ST_CP 9
#define SH_CP 10

class hardware {
    public:
        hardware();
        void initialize();
        unsigned char C74HC165();
        void C74HC595(unsigned char data);
};


#endif