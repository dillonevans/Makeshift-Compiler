#ifndef BCI_H
#define BCI_H

#include <cstdint>
enum : uint8_t
{
    RETURN,
    ADD,
    SUB,
    MULT,
    DIV,
    LOAD,
    JF,
    LT,
    GT,
    LTE,
    GTE,
    POP,
    JUMP,
    PRINT,
    AND,
    OR,
    LABEL,
    CALL,
    LOAD_LOCAL,
    SET_LOCAL
};

class ByteCodeInstruction
{
private:
    uint8_t opcode;
    int constant = 0;
public:
    ByteCodeInstruction(uint8_t opcode);
    ByteCodeInstruction(uint8_t opcode, int constant);
    uint8_t getOpcode();
    int getConstant();
    void setConstant(int constant);

};
#endif