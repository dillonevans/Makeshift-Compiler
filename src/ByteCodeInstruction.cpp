#include "../headers/ByteCodeInstruction.h"
#include <cstdint>
ByteCodeInstruction::ByteCodeInstruction(uint8_t opcode) : opcode{ opcode } {}
ByteCodeInstruction::ByteCodeInstruction(uint8_t opcode, int constant) : opcode{ opcode }, constant{ constant } {}

/**
 * Returns the instruction's opcode
 */
uint8_t ByteCodeInstruction::getOpcode()
{
    return opcode;
}

/**
 * Returns the constant following the opcode
 */
int ByteCodeInstruction::getConstant()
{
    return constant;
}
void ByteCodeInstruction::setConstant(int constant)
{
    this->constant = constant;
}
