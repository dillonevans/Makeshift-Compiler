#include "../headers/ByteCodeInstruction.h"
#include <cstdint>
ByteCodeInstruction::ByteCodeInstruction(uint8_t opcode) : opcode{opcode} {}
ByteCodeInstruction::ByteCodeInstruction(uint8_t opcode, int constant) : opcode{opcode}, constant{constant} {}

uint8_t ByteCodeInstruction::getOpcode(){
    return opcode;
}
int ByteCodeInstruction::getConstant(){
    return constant;
}
void ByteCodeInstruction::setConstant(int constant){
    this->constant = constant;
}
