# 8-Bit microprocessor 2.0

This project is the construction of an 8-bit microprocessor. <br>
<br>

## Instructions

| Item    | Description                                                              | code |
| :------ | :----------------------------------------------------------------------- | :--- |
| **HLT** | Stop processing                                                          | 0x00 |
| **NOP** | This instruction is used to waste time                                   | 0x01 |
| **OTI** | Add accumulator value to OTR                                             | 0x02 |
| **LDA** | Add UR value to accumulator                                              | 0x03 |
| **LDI** | Add argument to accumulator                                              | 0x04 |
| **ADD** | Add an argument to the accumulator                                       | 0x05 |
| **SUB** | Subtracts argument from the accumulator                                  | 0x06 |
| **STA** | Add accumulator value to UR                                              | 0x07 |
| **AND** | Does the logic and between accumulator and argument                      | 0x08 |
| **ORL** | Does the logic or between accumulator and argument                       | 0x09 |
| **XOR** | Does the logic xor between accumulator and argument                      | 0x0A |
| **NOT** | Invert the accumulator bits                                              | 0x0B |
| **GTA** | Conditional branch instruction                                           | 0x0C |
| **IFC** | Conditional branch instruction if flag c is enabled                      | 0x0D |
| **IFZ** | Conditional branch instruction if flag z is enabled                      | 0x0E |
| **IFE** | Conditional branch instruction if flag e is enabled                      | 0x0F |
| **ITI** | Add ITR value to accumulator                                             | 0x10 |
| **SHR** | Shift right accumulator                                                  | 0x11 |
| **SHL** | Shift left accumulator                                                   | 0x12 |
| **CPA** | Compares the accumulator with the argument                               | 0x13 |
| **ADA** | Add UR to accumulator                                                    | 0x14 |
| **SBA** | Subtracts UR to accumulator                                              | 0x15 |
| **ANA** | Does the logic and between accumulator and UR                            | 0x16 |
| **ORA** | Does the logic or between accumulator and UR                             | 0x17 |
| **XRA** | Does the logic xor between accumulator and UR                            | 0x18 |
| **SWA** | Reversing the nibbles                                                    | 0x19 |
| **PUH** | Adds the accumulator value to the memory stack                           | 0x1A |
| **POP** | Return and remove the last value from the memory stack                   | 0x1B |
| **CSR** | Calls a function located at the address of the argument                  | 0x1C |
| **RET** | Restores the counter to the content prior to calling the csr instruction | 0x1D |

<br>

## Registrars

Currently has five registrars:<br>

| Item                | Description                                  |
| :------------------ | :------------------------------------------- |
| **INSTRUCTION**     | Instruction                                  |
| **ADD_INSTRUCTION** | Instruction address                          |
| **ARGUMENT**        | Argument                                     |
| **ACC**             | Accumulator                                  |
| **ADD_ROM**         | Current address of rom memory                |
| **BR**              | 8-bit registers to aid in logical operations |
| **UR**              | Ten registers for the user to use            |
| **OTR**             | Output register                              |
| **ITR**             | Input register                               |

<br>

## Flags

Currently has two flags: <br>

| Item      | Description                                                         |
| :-------- | :------------------------------------------------------------------ |
| **CFLAG** | Enabled if the result of some arithmetic operation is more than 255 |
| **ZFLAG** | Enabled if accumulator is zero                                      |
| **EFLAG** | Enabled if an accumulator is equal to the argument                  |

## Memory Stack

The memory stack has a ten levels.<br>