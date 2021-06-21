#include <vector>
#include "ByteCodeInstruction.h"
#include <string>
#include <cstdint>
#include <stack>
#include "CallFrame.h"
class VM
{
private:
    std::string disassembleInstruction(ByteCodeInstruction instruction);
    std::stack<CallFrame> callStack;
    CallFrame* currentFrame;
    std::vector<ByteCodeInstruction> instructions;
    std::vector<int> stack;

public:
    VM(std::vector<ByteCodeInstruction> instructions);
    void run();
    void retrieveOperands(int& a, int& b);
    void disassembleInstruction();
    void dumpByteCode();
};