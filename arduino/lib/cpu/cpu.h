#ifndef ARDUINO_CPU_H
#define ARDUINO_CPU_H


class cpu {
    public:
        cpu(unsigned char* bytes);
        void start();
    private:
        unsigned char* ROM;
};

#endif
