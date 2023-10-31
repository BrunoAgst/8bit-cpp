#include "ula.h"
#include "Arduino.h"

ula::ula(){}

void ula::addExec(
        unsigned char* rom,
        unsigned int* cycle,
        unsigned int* counter,
        unsigned char* ZFLAG,
        unsigned char* CFLAG,
        unsigned char* ACC,
        unsigned char* ARGUMENT
){
    if(*cycle == 3){
        *ARGUMENT = rom[*counter];
        *counter++;
        *cycle++;
        return;
    }

    if(*cycle == 4){
        BR = *ARGUMENT;
        *cycle++;;
        return;
    }
    if(*cycle == 5){
        *CFLAG = (*ACC + BR) >> 8;
        *ACC += BR;
        *ZFLAG = *ACC ? 0 : 1;
        *cycle = 0;
    }
}

void ula::subExec(
        unsigned char* rom,
        unsigned int* cycle,
        unsigned int* counter,
        unsigned char* ZFLAG,
        unsigned char* CFLAG,
        unsigned char* ACC,
        unsigned char* ARGUMENT
){
    if(*cycle == 3){
        *ARGUMENT = rom[*counter];
        *counter++;
        *cycle++;
        return;
    }

    if(*cycle == 4){
        BR = *ARGUMENT;
        *cycle++;;
        return;
    }
    if(*cycle == 5){
        *CFLAG = (*ACC + BR) >> 8;
        ACC -= BR;
        *ZFLAG = *ACC ? 0 : 1;
        *cycle = 0;
    }
}


void ula::andExec(
        unsigned char* _rom,
        unsigned int* cycle,
        unsigned int* counter,
        unsigned char* ZFLAG,
        unsigned char* ACC,
        unsigned char* ARGUMENT
){
    if(*cycle == 3){
        *ARGUMENT = _rom[*counter];
        *counter++;
        *cycle++;
        return;
    }
    if(*cycle == 4){
        *ACC &= *ARGUMENT;
        *ZFLAG = *ACC ? 0 : 1;
        *cycle = 0;
    }
}

void ula::orlExec(
        unsigned char* _rom,
        unsigned int* cycle,
        unsigned int* counter,
        unsigned char* ZFLAG,
        unsigned char* ACC ,
        unsigned char* ARGUMENT
){
    if(*cycle == 3){
        *ARGUMENT = _rom[*counter];
        *counter++;
        *cycle++;
        return;
    }
    if(*cycle == 4){
        *ACC |= *ARGUMENT;
        *ZFLAG = *ACC ? 0 : 1;
        *cycle = 0;
    }
}

void ula::xorExec(
        unsigned char* _rom,
        unsigned int* cycle,
        unsigned int* counter,
        unsigned char* ZFLAG,
        unsigned char* ACC,
        unsigned char* ARGUMENT
){
    if(*cycle == 3){
        *ARGUMENT = _rom[*counter];
        *counter++;
        *cycle++;
        return;
    }
    if(*cycle == 4){
        *ACC ^= *ARGUMENT;
        *ZFLAG = *ACC ? 0 : 1;
        *cycle = 0;
    }
}

void ula::notExec(
        unsigned int* cycle,
        unsigned char* ZFLAG,
        unsigned char* ACC
){
    if(*cycle == 3){
        *ACC = ~*ACC;
        *ZFLAG = *ACC ? 0 : 1;
        *cycle = 0;
    }
}

void ula::shrExec(
        unsigned char* _rom,
        unsigned int* cycle,
        unsigned int* counter,
        unsigned char* ZFLAG,
        unsigned char* ACC,
        unsigned char* ARGUMENT
){
    if(*cycle == 3){
        *ARGUMENT = _rom[*counter];
        *counter++;
        *cycle++;
        return;
    }

    if(*cycle == 4){
        *ACC >>= *ARGUMENT;
        *ZFLAG = *ACC ? 0 : 1;
        *cycle = 0;
    }
}

void ula::shlExec(
        unsigned char* _rom,
        unsigned int* cycle,
        unsigned int* counter,
        unsigned char* ZFLAG,
        unsigned char* ACC,
        unsigned char* ARGUMENT
){
    if(*cycle == 3){
        *ARGUMENT = _rom[*counter];
        *counter++;
        *cycle++;
        return;
    }

    if(*cycle == 4){
        *ACC <<= *ARGUMENT;
        *ZFLAG = *ACC ? 0 : 1;
        *cycle = 0;
    }
}

void ula::cpaExec(
        unsigned char* _rom,
        unsigned int* cycle,
        unsigned int* counter,
        unsigned char* EFLAG,
        unsigned char* ACC,
        unsigned char* ARGUMENT
){
    if(*cycle == 3){
        *ARGUMENT = _rom[*counter];
        *counter++;
        *cycle++;
        return;
    }
    if(*cycle == 4){
        BR = *ARGUMENT;
        *cycle++;
        return;
    }
    if(*cycle == 5){
        *EFLAG = (*ACC == BR) ? 1 : 0;
        *cycle = 0;
    }
}

void ula::adaExec(
        unsigned char* _rom,
        unsigned int* cycle,
        unsigned int* counter,
        unsigned char* ZFLAG,
        unsigned char* ACC,
        unsigned char* CFLAG,
        unsigned char* UR,
        unsigned char* ARGUMENT

){
    if(*cycle == 3){
        *ARGUMENT = _rom[*counter];
        *counter++;
        *cycle++;
        return;
    }
    if(*cycle == 4){
        if(*ARGUMENT>= 0x00 && *ARGUMENT<= 0x09){
            BR = UR[*ARGUMENT];
            *cycle++;
            return;
        } else{
            Serial.print("[Error] UR[");
            Serial.print(*ARGUMENT, HEX);
            Serial.println("] is invalid");
            *cycle = 0;
            return;
        }
    }
    if(*cycle == 5){
        *CFLAG = (*ACC + BR) >> 8;
        *ACC += BR;
        *ZFLAG = *ACC ? 0 : 1;
        *cycle = 0;
    }
}

void ula::sbaExec(
        unsigned char* _rom,
        unsigned int* cycle,
        unsigned int* counter,
        unsigned char* ZFLAG,
        unsigned char* ACC,
        unsigned char* CFLAG,
        unsigned char* UR,
        unsigned char* ARGUMENT
){
    if(*cycle == 3){
        *ARGUMENT= _rom[*counter];
        *counter++;
        *cycle++;
        return;
    }
    if(*cycle == 4){
        if(*ARGUMENT>= 0x00 && *ARGUMENT<= 0x09){
            BR = UR[*ARGUMENT];
            *cycle++;
            return;
        } else{
            Serial.print("[Error] UR[");
            Serial.print(*ARGUMENT, HEX);
            Serial.println("] is invalid");
            *cycle = 0;
            return;
        }
    }
    if(*cycle == 5){
        *CFLAG = (*ACC + BR) >> 8;
        *ACC -= BR;
        *ZFLAG = *ACC ? 0 : 1;
        *cycle = 0;
    }
}

void ula::anaExec(
        unsigned char* _rom,
        unsigned int* cycle,
        unsigned int* counter,
        unsigned char* ZFLAG,
        unsigned char* ACC,
        unsigned char* CFLAG,
        unsigned char* UR,
        unsigned char* ARGUMENT
){
    if(*cycle == 3){
        *ARGUMENT= _rom[*counter];
        *counter++;
        *cycle++;
        return;
    }
    if(*cycle == 4){
        if(*ARGUMENT>= 0x00 && *ARGUMENT<= 0x09){
            BR = UR[*ARGUMENT];
            *cycle++;
            return;
        } else{
            Serial.print("[Error] UR[");
            Serial.print(*ARGUMENT, HEX);
            Serial.println("] is invalid");
            *cycle = 0;
            return;
        }
    }
    if(*cycle == 5){
        *CFLAG = (*ACC + BR) >> 8;
        *ACC &= BR;
        *ZFLAG = *ACC ? 0 : 1;
        *cycle = 0;
    }
}

void ula::oraExec(
        unsigned char* _rom,
        unsigned int* cycle,
        unsigned int* counter,
        unsigned char* ZFLAG,
        unsigned char* ACC,
        unsigned char* CFLAG,
        unsigned char* UR,
        unsigned char* ARGUMENT
){
    if(*cycle == 3){
        *ARGUMENT= _rom[*counter];
        *counter++;
        *cycle++;
        return;
    }
    if(*cycle == 4){
        if(*ARGUMENT>= 0x00 && *ARGUMENT<= 0x09){
            BR = UR[*ARGUMENT];
            *cycle++;
            return;
        } else{
            Serial.print("[Error] UR[");
            Serial.print(*ARGUMENT, HEX);
            Serial.println("] is invalid");
            *cycle = 0;
            return;
        }
    }
    if(*cycle == 5){
        *CFLAG = (*ACC + BR) >> 8;
        *ACC |= BR;
        *ZFLAG = *ACC ? 0 : 1;
        *cycle = 0;
    }
}

void ula::xraExec(
        unsigned char* _rom,
        unsigned int* cycle,
        unsigned int* counter,
        unsigned char* ZFLAG,
        unsigned char* ACC,
        unsigned char* CFLAG,
        unsigned char* UR,
        unsigned char* ARGUMENT
){
    if(*cycle == 3){
        *ARGUMENT= _rom[*counter];
        *counter++;
        *cycle++;
        return;
    }
    if(*cycle == 4){
        if(*ARGUMENT>= 0x00 && *ARGUMENT<= 0x09){
            BR = UR[*ARGUMENT];
            *cycle++;
            return;
        } else{
            Serial.print("[Error] UR[");
            Serial.print(*ARGUMENT, HEX);
            Serial.println("] is invalid");
            *cycle = 0;
            return;
        }
    }
    if(*cycle == 5){
        *CFLAG = (*ACC + BR) >> 8;
        *ACC ^= BR;
        *ZFLAG = *ACC ? 0 : 1;
        *cycle = 0;
    }
}

void ula::swaExec(
        unsigned char* ACC,
        unsigned int* cycle
){
    if (*cycle == 3){
        *ACC = (*ACC & 0x0F) << 4 | (*ACC & 0xF0) >> 4;
        *cycle = 0;
    }
}