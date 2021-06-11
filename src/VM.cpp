#include "../headers/VM.h"
#include <iostream>
#include <string>
#include <iomanip>
VM::VM(std::vector<ByteCodeInstruction> instructions) : instructions{instructions} {}

void VM::dumpByteCode()
{
    for (auto i : instructions)
    {
        switch(i.getOpcode())
        {
            case ADD:
            case MULT:
            case DIV:
            case SUB:
            case GT:
            case LT:
            case POP:
            case PRINT:
            case AND:
            case OR:
                std::cout << "0x" << std::setfill('0') << std::setw(4) << std::hex << +i.getOpcode() << "\n";
                break;
            case LOAD:
            case JF:
            case JUMP:
                std::cout << "0x" << std::setfill('0') << std::setw(4) << std::hex << +i.getOpcode() << "\t0x"  << std::setfill('0') << std::setw(4) << i.getConstant()<< "\n";
                break;
        }
    }
        std::cout << "\n";
}

std::string VM::disassembleInstruction(ByteCodeInstruction instruction)
{
    uint8_t opcode = instruction.getOpcode();
    int constant = instruction.getConstant();
    switch(opcode)
    {
        case ADD:
            return "ADD";
        case SUB:
            return "SUB";
        case MULT:
            return "MULT";
        case DIV:
            return "DIV";
        case JF:
            return "JF\t" + std::to_string(constant);
        case POP:
            return "POP";
        case LT:
            return "LT";
        case GT:
            return "GT";
        case AND:
            return "AND";
        case OR:
            return "OR";
        case LOAD:
            return "LOAD\t" + std::to_string(constant);
        case JUMP:
            return "JUMP\t" + std::to_string(constant);
        case PRINT:
            return "PRINT\t";
       
    }
    return "OOF";
}
void VM::disassembleInstruction()
{
    std::cout << "\tDISSASEMBLY\n";
    for (int i = 0; i < instructions.size(); i++)
    {
        auto x = instructions[i];
        std::cout << "Instruction " << std::dec << i << ":\t" << disassembleInstruction(x) << "\n";
    }
}

void VM::retrieveOperands(int &a, int &b)
{
    a = stack[stack.size() - 1];
    stack.pop_back();
    b = stack[stack.size() - 1];
    stack.pop_back();
}

void VM::run()
{
    int a = 0, b = 0;
    for (int ip = 0; ip < instructions.size(); ip++)
    {
        //std::cout << "IP AT " << ip << "\n";
        switch (instructions[ip].getOpcode())
        {
            case ADD:
                retrieveOperands(a,b);
                stack.push_back(b + a);
                break;
            case DIV:
                retrieveOperands(a,b);
                stack.push_back(b / a);
                break;
            case MULT:
                retrieveOperands(a,b);
                stack.push_back(b * a);
                break;
            case SUB:
                retrieveOperands(a,b);
                stack.push_back(b - a);
                break;
            case AND:
                retrieveOperands(a,b);
                stack.push_back(b && a);
                break;
            case OR: 
                retrieveOperands(a,b);
                stack.push_back(b || a);
                break;
            case LOAD:
                stack.push_back(instructions[ip].getConstant());
                break;
            case LT:
                retrieveOperands(a,b);
                stack.push_back(b < a);
                break;
            case GT:
                retrieveOperands(a,b);
                stack.push_back(b > a);
                break;
            case POP:
                stack.pop_back();
                break;
            case JF:
                a = stack[stack.size() - 1];
                if (!a) {ip = instructions[ip].getConstant() - 1;}
                break;
            case JUMP:
                ip = instructions[ip].getConstant() - 1;
                break;
            case PRINT:
                a = stack[stack.size() - 1];
                stack.pop_back();
                std::cout << a << "\n";
            default:
                break;
        }
    }
}