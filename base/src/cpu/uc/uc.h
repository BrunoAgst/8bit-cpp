#ifndef BASE_UC_H
#define BASE_UC_H
//instructions

#define HLT 0x00
#define NOP 0x01
#define OTI 0x02
#define LDA 0x03
#define LDI 0x04
#define ADD 0x05
#define SUB 0x06
#define STA 0x07
#define AND 0x08
#define ORL 0x09
#define XOR 0x0A
#define NOT 0X0B
#define GTA 0X0C
#define IFC 0x0D
#define IFZ 0x0E
#define IFE 0x0F
#define ITI 0x10
#define SHR 0x11
#define SHL 0x12
#define CPA 0x13
#define ADA 0x14
#define SBA 0x15
#define ANA 0x16
#define ORA 0x17
#define XRA 0x18
#define SWA 0x19
#define PUH 0x1A
#define POP 0x1B
#define CSR 0x1C
#define RET 0x1D

class uc {
public:
    uc(unsigned char* rom);
    void fetch();
private:
    unsigned int counter;
    unsigned int cycle;
    unsigned char* _rom;
    unsigned int level;

    // registers
    unsigned char ADD_ROM;
    unsigned char ADD_INSTRUCTION;
    unsigned char INSTRUCTION;
    unsigned char OTR;
    unsigned char ITR;
    unsigned char ACC;
    unsigned char UR[10];
    unsigned char ARGUMENT;

    //stack
    unsigned char stack[10];
    unsigned int counterStack;

    // flags
    unsigned char ZFLAG;
    unsigned char CFLAG;
    unsigned char EFLAG;

    // functions
    void getInstruction();
    void searchInstruction();
    int selectInstruction(unsigned char opcode);
    void searchOperation(unsigned char instruction);
    void printOutput();
    void nopExec();
    void itiExec();
    void otiExec();
    void ldiExec();
    void ldaExec();
    void staExec();
    void gtaExec();
    void ifcExec();
    void ifzExec();
    void ifeExec();
    void puhExec();
    void popExec();
    void csrExec();
    void retExec();
    void addStack(unsigned char value);
    unsigned char subStack();
};


#endif
