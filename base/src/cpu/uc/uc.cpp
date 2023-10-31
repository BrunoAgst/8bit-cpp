#include "uc.h"
#include "../ula/ula.h"
#include <iostream>
#include <iomanip>

using std::cout;
using std::cin;
using std::endl;
using std::hex;
using std::setw;
using std::setfill;

uc::uc(unsigned char* rom)
: _rom(rom) {
    counter = 0;
    cycle = 0;
    EFLAG = 0x00;
    CFLAG = 0x00;
    ZFLAG = 0x00;
    ITR = 0x00;
    ARGUMENT = 0x00;
    ACC = 0x00;
    level = 1;
    for(int i = 0; i < 10; i++)
        UR[i] = 0x00;
    for(int i = 0; i < 10; i++)
        stack[i] = 0x00;
    counterStack = (sizeof(stack) - sizeof(stack[0]));
}

void uc::fetch(){
    while(level){
        switch (cycle){
            case 0:
            case 1:
                getInstruction();
                break;
            case 2:
                searchInstruction();
                break;
            case 3:
            case 4:
            case 5:
                searchOperation(INSTRUCTION);
                break;
            default:
                break;
        }
    }
}

void uc::getInstruction(){
    if(cycle == 0){
        ADD_ROM = counter;
        cycle ++;
        return;
    }

    if(cycle == 1){
        ADD_INSTRUCTION = _rom[counter];
        counter ++;
        cycle ++;
        return;
    }
}

void uc::searchInstruction(){
    ADD_ROM = counter;
    if(!selectInstruction(ADD_INSTRUCTION
    ))
        return;
    cycle ++;
}

int uc::selectInstruction(unsigned char opcode){
    int valid = 0;

    switch (opcode){
        case 0x00:
            INSTRUCTION = HLT;
            level = 0;
            valid = 0;
            break;
        case 0x01:
            INSTRUCTION = NOP;
            valid = 1;
            break;
        case 0x02:
            INSTRUCTION = OTI;
            valid = 1;
            break;
        case 0x03:
            INSTRUCTION = LDA;
            valid = 1;
            break;
        case 0x04:
            INSTRUCTION = LDI;
            valid = 1;
            break;
        case 0x05:
            INSTRUCTION = ADD;
            valid = 1;
            break;
        case 0x06:
            INSTRUCTION = SUB;
            valid = 1;
            break;
        case 0x07:
            INSTRUCTION = STA;
            valid = 1;
            break;
        case 0x08:
            INSTRUCTION = AND;
            valid = 1;
            break;
        case 0x09:
            INSTRUCTION = ORL;
            valid = 1;
            break;
        case 0x0A:
            INSTRUCTION = XOR;
            valid = 1;
            break;
        case 0x0B:
            INSTRUCTION = NOT;
            valid = 1;
            break;
        case 0x0C:
            INSTRUCTION = GTA;
            valid = 1;
            break;
        case 0x0D:
            INSTRUCTION = IFC;
            valid = 1;
            break;
        case 0x0E:
            INSTRUCTION = IFZ;
            valid = 1;
            break;
        case 0x0F:
            INSTRUCTION = IFE;
            valid = 1;
            break;
        case 0x10:
            INSTRUCTION = ITI;
            valid = 1;
            break;
        case 0x11:
            INSTRUCTION = SHR;
            valid = 1;
            break;
        case 0x12:
            INSTRUCTION = SHL;
            valid = 1;
            break;
        case 0x13:
            INSTRUCTION = CPA;
            valid = 1;
            break;
        case 0x14:
            INSTRUCTION = ADA;
            valid = 1;
            break;
        case 0x15:
            INSTRUCTION = SBA;
            valid = 1;
            break;
        case 0x16:
            INSTRUCTION = ANA;
            valid = 1;
            break;
        case 0x17:
            INSTRUCTION = ORA;
            valid = 1;
            break;
        case 0x18:
            INSTRUCTION = XRA;
            valid = 1;
            break;
        case 0x19:
            INSTRUCTION = SWA;
            valid = 1;
            break;
        case 0x1A:
            INSTRUCTION = PUH;
            valid = 1;
            break;
        case 0x1B:
            INSTRUCTION = POP;
            valid = 1;
            break;
        case 0x1C:
            INSTRUCTION = CSR;
            valid = 1;
            break;
        case 0x1D:
            INSTRUCTION = RET;
            valid = 1;
            break;
        default:
            cout << "[Error] Instruction not found" << endl;
            level = 0;
            valid = 0;
            break;
    }

    return valid;
}

void uc::searchOperation(unsigned char instruction){
    ula u;
    switch (instruction){
        case NOP:
            nopExec();
            break;
        case OTI:
            otiExec();
            break;
        case LDA:
            ldaExec();
            break;
        case LDI:
            ldiExec();
            break;
        case ADD:
            u.addExec(_rom, &cycle, &counter, &ZFLAG, &CFLAG, &ACC, &ARGUMENT);
            break;
        case SUB:
            u.subExec(_rom, &cycle, &counter, &ZFLAG, &CFLAG, &ACC, &ARGUMENT);
            break;
        case STA:
            staExec();
            break;
        case AND:
            u.andExec(_rom, &cycle, &counter, &ZFLAG, &ACC, &ARGUMENT);
            break;
        case ORL:
            u.orlExec(_rom, &cycle, &counter, &ZFLAG, &ACC, &ARGUMENT);
            break;
        case XOR:
            u.xorExec(_rom, &cycle, &counter, &ZFLAG, &ACC, &ARGUMENT);
            break;
        case NOT:
            u.notExec(&cycle, &ZFLAG, &ACC);
            break;
        case GTA:
            gtaExec();
            break;
        case IFC:
            ifcExec();
            break;
        case IFZ:
            ifzExec();
            break;
        case IFE:
            ifeExec();
            break;
        case ITI:
            itiExec();
            break;
        case SHR:
            u.shrExec(_rom, &cycle, &counter, &ZFLAG, &ACC, &ARGUMENT);
            break;
        case SHL:
            u.shlExec(_rom, &cycle, &counter, &ZFLAG, &ACC, &ARGUMENT);
            break;
        case CPA:
            u.cpaExec(_rom, &cycle, &counter, &EFLAG, &ACC, &ARGUMENT);
            break;
        case ADA:
            u.adaExec(_rom, &cycle, &counter, &ZFLAG, &ACC, &CFLAG, UR, &ARGUMENT);
            break;
        case SBA:
            u.sbaExec(_rom, &cycle, &counter, &ZFLAG, &ACC, &CFLAG, UR, &ARGUMENT);
            break;
        case ANA:
            u.anaExec(_rom, &cycle, &counter, &ZFLAG, &ACC, &CFLAG, UR, &ARGUMENT);
            break;
        case ORA:
            u.oraExec(_rom, &cycle, &counter, &ZFLAG, &ACC, &CFLAG, UR, &ARGUMENT);
            break;
        case XRA:
            u.xraExec(_rom, &cycle, &counter, &ZFLAG, &ACC, &CFLAG, UR, &ARGUMENT);
            break;
        case SWA:
            u.swaExec(&ACC, &cycle);
            break;
        case PUH:
            puhExec();
            break;
        case POP:
            popExec();
            break;
        case CSR:
            csrExec();
            break;
        case RET:
            retExec();
            break;
        default:
            break;
    }
}

void uc::nopExec(){
    cycle = 0;
}

void uc::itiExec(){
    if(cycle == 3){
        unsigned int data = 0;
        ITR = data;
        cycle ++;
        return;
    }

    if(cycle == 4){
        ACC = ITR;
        cycle = 0;
    }
}

void uc::otiExec(){
    if (cycle == 3){
        OTR = ACC;
        printOutput();
        cycle = 0;
    }
}

void uc::ldiExec(){
    if(cycle == 3){
        ARGUMENT = _rom[counter];
        counter ++;
        cycle ++;
        return;
    }

    if(cycle == 4){
        ACC = ARGUMENT;
        cycle = 0;
    }
}

void uc::ldaExec(){
    if(cycle == 3){
        ARGUMENT = _rom[counter];
        counter ++;
        cycle ++;
        return;
    }

    if(cycle == 4){
        if(ARGUMENT >= 0x00 && ARGUMENT <= 0x09){
            ACC = UR[ARGUMENT];
            ZFLAG = ACC ? 0 : 1;
            cycle = 0;
        } else {
            cout << "[Error] UR[" << hex << setw(2) << setfill('0') << static_cast<int>(ARGUMENT) << "] is invalid" << endl;
            cycle = 0;
        }
    }
}

void uc::staExec(){
    if(cycle == 3){
        ARGUMENT = _rom[counter];
        counter++;
        cycle++;
        return;
    }

    if(cycle == 4){
        if(ARGUMENT >= 0x00 && ARGUMENT <= 0x09){
            UR[ARGUMENT] = ACC;
            cycle = 0;
        } else{
            cout << "[Error] UR[" << hex << setw(2) << setfill('0') << static_cast<int>(ARGUMENT) << "] is invalid" << endl;
            cycle = 0;
        }
    }
}

void uc::gtaExec(){
    if(cycle == 3){
        ARGUMENT = _rom[counter];
        counter++;
        cycle++;
        return;
    }
    if(cycle == 4){
        counter = ARGUMENT;
        cycle = 0;
    }
}

void uc::ifeExec(){
    if(cycle == 3){
        ARGUMENT = _rom[counter];
        counter++;
        cycle++;
        return;
    }

    if(cycle == 4){
        if(EFLAG == 1){
            counter = ARGUMENT;
            cycle = 0;
        }
        else{
            cycle = 0;
        }
    }
}

void uc::ifzExec(){
    if(cycle == 3){
        ARGUMENT = _rom[counter];
        counter++;
        cycle++;
        return;
    }

    if(cycle == 4){
        if(ZFLAG == 1){
            counter = ARGUMENT;
            cycle = 0;
        }
        else{
            cycle = 0;
        }
    }
}

void uc::ifcExec(){
    if(cycle == 3){
        ARGUMENT = _rom[counter];
        counter++;
        cycle++;
        return;
    }

    if(cycle == 4){
        if(CFLAG == 1){
            counter = ARGUMENT;
            cycle = 0;
        }
        else{
            cycle = 0;
        }
    }
}

void uc::puhExec(){
    if(cycle == 3){
        addStack(ACC);
        cycle = 0;
    }
}

void uc::popExec(){
    if(cycle == 3){
        ACC = subStack();
        ZFLAG = ACC ? 0 : 1;
        cycle = 0;
    }
}

void uc::addStack(unsigned char value){
    stack[counterStack] = value;
    counterStack -= 1;
}

unsigned char uc::subStack(){
    counterStack ++;
    unsigned char value = stack[counterStack];
    stack[counterStack] = 0x00;
    return value;
}

void uc::csrExec(){
    if(cycle == 3){
        ARGUMENT = _rom[counter];
        counter++;
        cycle++;
        return;
    }

    if(cycle == 4){
        addStack(counter);
        counter = ARGUMENT;
        cycle = 0;
    }
}

void uc::retExec(){
    if(cycle == 3){
        counter = subStack();
        cycle = 0;
    }
}

void uc::printOutput(){
    cout << "********************" << endl;
    cout << "   COUNTERS   " << endl;
    cout << "********************" << endl;
    cout << "Cycle: " << cycle << endl;
    cout << "Counters: " << counter << endl;
    cout << endl;
    cout << "********************" << endl;
    cout << "   REGISTERS   " << endl;
    cout << "********************" << endl;
    cout << "ARGUMENT: 0x" << hex << setw(2) << setfill('0') << static_cast<int>(ARGUMENT) << endl;
    cout << "INSTRUCTION: " << setw(2) << setfill('0') << static_cast<int>(INSTRUCTION) << endl;
    cout << "ACC: 0x" << hex << setw(2) << setfill('0') << static_cast<int>(ACC) << endl;
    cout << "OTR: 0x" << hex << setw(2) << setfill('0') << static_cast<int>(OTR) << endl;
    cout << "ITR: 0x" << hex << setw(2) << setfill('0') << static_cast<int>(ITR) << endl;
    for(int i = 0; i <= 9; i++)
        cout << "UR[" << i << "]: 0x" << hex << setw(2) << setfill('0') << static_cast<int>(UR[i]) << endl;
    cout << endl;
    cout << "********************" << endl;
    cout << "   FLAGS   " << endl;
    cout << "********************" << endl;
    cout << "CFLAG: 0x" << hex << setw(2) << setfill('0') << static_cast<int>(CFLAG) << endl;
    cout << "EFLAG: 0x" << hex << setw(2) << setfill('0') << static_cast<int>(EFLAG) << endl;
    cout << "ZFLAG: 0x" << hex << setw(2) << setfill('0') << static_cast<int>(ZFLAG) << endl;
    cout << endl;
    cout << "********************" << endl;
    cout << "   STACK   " << endl;
    cout << "********************" << endl;
    for(int i = 0; i < 10; i++)
        cout << "STACK[" << i << "]: 0x" << hex << setw(2) << setfill('0') << static_cast<int>(stack[i]) << endl;
    cout << "Counter Stack: " << counterStack << endl;
}