#include "cpu.h"
#include "./uc/uc.cpp"

cpu::cpu(unsigned char* bytes) : ROM(bytes){};

void cpu::start(){
    uc u(ROM);
    u.fetch();
}