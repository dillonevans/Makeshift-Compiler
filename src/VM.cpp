#include "../headers/VM.h"
#include <iostream>
#include <string>
#include <iomanip>
VM::VM(std::vector<ByteCodeInstruction> instructions) : instructions{ instructions } {}

void VM::dumpByteCode()
{
    for (auto i : instructions)
    {
        switch (i.getOpcode())
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
            case RETURN:
                std::cout << "0x" << std::setfill('0') << std::setw(2) << std::hex << +i.getOpcode() << "\n";
                break;
            case LOAD:
            case JF:
            case JUMP:
            case CALL:
            case LOAD_LOCAL:
            case SET_LOCAL:
                std::cout << "0x" << std::setfill('0') << std::setw(2) << std::hex << +i.getOpcode() << "\t0x" << std::setfill('0') << std::setw(4) << i.getConstant() << "\n";
                break;
        }
    }
    std::cout << "\n";
}

std::string VM::disassembleInstruction(ByteCodeInstruction instruction)
{
    uint8_t opcode = instruction.getOpcode();
    int constant = instruction.getConstant();
    switch (opcode)
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
            return "JF\t\t" + std::to_string(constant);
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
        case RETURN:
            return "RETURN";
        case LOAD:
            return "LOAD\t\t" + std::to_string(constant);
        case JUMP:
            return "JUMP\t\t" + std::to_string(constant);
        case PRINT:
            return "PRINT\t\t";
        case LABEL:
            return "L" + std::to_string(constant);
        case CALL:
            return "CALL\t\t" + std::to_string(constant);
        case LOAD_LOCAL:
            return "LOAD_LOCAL\t" + std::to_string(constant);
        case SET_LOCAL:
            return "SET_LOCAL\t" + std::to_string(constant);

    }
    return "UNKNOWN";
}
void VM::disassembleInstruction()
{
    std::cout << "\tDISSASEMBLY\n";
    for (int i = 0; i < instructions.size(); i++)
    {
        auto x = instructions[i];
        std::cout << std::dec << i << ":\t" << disassembleInstruction(x) << "\n";
    }
}

void VM::retrieveOperands(int& a, int& b)
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

        //std::cout << "IP: " << ip << ". Stack Size: " << stack.size() << ". \n";
        switch (instructions[ip].getOpcode())
        {
            case ADD:
                retrieveOperands(a, b);
                stack.push_back(b + a);
                break;
            case DIV:
                retrieveOperands(a, b);
                stack.push_back(b / a);
                break;
            case MULT:
                retrieveOperands(a, b);
                stack.push_back(b * a);
                break;
            case SUB:
                retrieveOperands(a, b);
                stack.push_back(b - a);
                break;
            case AND:
                retrieveOperands(a, b);
                stack.push_back(b && a);
                break;
            case OR:
                retrieveOperands(a, b);
                stack.push_back(b || a);
                break;
            case LOAD:
                stack.push_back(instructions[ip].getConstant());
                break;
            case LT:
                retrieveOperands(a, b);
                stack.push_back(b < a);
                break;
            case GT:
                retrieveOperands(a, b);
                stack.push_back(b > a);
                break;
            case POP:
                stack.pop_back();
                break;
            case JF:
                a = stack[stack.size() - 1];
                if (!a)
                {
                    ip = instructions[ip].getConstant() - 1;
                }
                break;
            case JUMP:
                ip = instructions[ip].getConstant() - 1;
                break;
            case PRINT:
                a = stack[stack.size() - 1];
                stack.pop_back();
                std::cout << a << "\n";
                break;
            case LABEL:
                continue;
            case CALL:
                callStack.push(CallFrame(stack.size()));
                this->currentFrame = &callStack.top();
                ip = instructions[ip].getConstant() - 1;
                break;
            case RETURN:
                callStack.pop();
                this->currentFrame = &callStack.top();
                ip = stack[stack.size() - 1];
                stack.pop_back();

                break;
            case LOAD_LOCAL:
                // std::cout << "Stack size: " << stack.size() << "\n";
                // std::cout << "TEST: " << this->currentFrame->basePointerOffset + instructions[ip].getConstant() << "\n";
                stack.push_back(stack[this->currentFrame->basePointerOffset + instructions[ip].getConstant()]);
                break;
            case SET_LOCAL:
                stack[this->currentFrame->basePointerOffset + instructions[ip].getConstant()] = stack.back();
                stack.pop_back();
                break;
            default:
                break;
        }
    }
}