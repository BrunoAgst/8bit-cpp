#ifndef BASE_ULA_H
#define BASE_ULA_H


class ula {
public:
    ula();

    //functions instructions
    void subExec(
            unsigned char* _rom,
            unsigned int* cycle,
            unsigned int* counter,
            unsigned char* ZFLAG,
            unsigned char* CFLAG,
            unsigned char* ACC,
            unsigned char* ARGUMENT
    );
    void addExec(
            unsigned char* _rom,
            unsigned int* cycle,
            unsigned int* counter,
            unsigned char* ZFLAG,
            unsigned char* CFLAG,
            unsigned char* ACC,
            unsigned char* ARGUMENT
    );
    void andExec(
            unsigned char* _rom,
            unsigned int* cycle,
            unsigned int* counter,
            unsigned char* ZFLAG,
            unsigned char* ACC,
            unsigned char* ARGUMENT
    );
    void orlExec(
            unsigned char* _rom,
            unsigned int* cycle,
            unsigned int* counter,
            unsigned char* ZFLAG,
            unsigned char* ACC,
            unsigned char* ARGUMENT
    );
    void xorExec(
            unsigned char* _rom,
            unsigned int* cycle,
            unsigned int* counter,
            unsigned char* ZFLAG,
            unsigned char* ACC,
            unsigned char* ARGUMENT
    );
    void notExec(
            unsigned int* cycle,
            unsigned char* ZFLAG,
            unsigned char* ACC
    );
    void shrExec(
            unsigned char* _rom,
            unsigned int* cycle,
            unsigned int* counter,
            unsigned char* ZFLAG,
            unsigned char* ACC,
            unsigned char* ARGUMENT
    );
    void shlExec(
            unsigned char* _rom,
            unsigned int* cycle,
            unsigned int* counter,
            unsigned char* ZFLAG,
            unsigned char* ACC,
            unsigned char* ARGUMENT
    );
    void cpaExec(
            unsigned char* _rom,
            unsigned int* cycle,
            unsigned int* counter,
            unsigned char* EFLAG,
            unsigned char* ACC,
            unsigned char* ARGUMENT

    );
    void adaExec(
            unsigned char* _rom,
            unsigned int* cycle,
            unsigned int* counter,
            unsigned char* ZFLAG,
            unsigned char* ACC,
            unsigned char* CFLAG,
            unsigned char* ur,
            unsigned char* ARGUMENT
    );
    void sbaExec(
            unsigned char* _rom,
            unsigned int* cycle,
            unsigned int* counter,
            unsigned char* ZFLAG,
            unsigned char* ACC,
            unsigned char* CFLAG,
            unsigned char* ur,
            unsigned char* ARGUMENT
    );
    void anaExec(
            unsigned char* _rom,
            unsigned int* cycle,
            unsigned int* counter,
            unsigned char* ZFLAG,
            unsigned char* ACC,
            unsigned char* CFLAG,
            unsigned char* ur,
            unsigned char* ARGUMENT
    );
    void oraExec(
            unsigned char* _rom,
            unsigned int* cycle,
            unsigned int* counter,
            unsigned char* ZFLAG,
            unsigned char* ACC,
            unsigned char* CFLAG,
            unsigned char* ur,
            unsigned char* ARGUMENT
    );
    void xraExec(
            unsigned char* _rom,
            unsigned int* cycle,
            unsigned int* counter,
            unsigned char* ZFLAG,
            unsigned char* ACC,
            unsigned char* CFLAG,
            unsigned char* ur,
            unsigned char* ARGUMENT
    );
    void swaExec(
            unsigned char* ACC,
            unsigned int* cycle
    );

    private:
        // registers
        unsigned char BR;
};


#endif
