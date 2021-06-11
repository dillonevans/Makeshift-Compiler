#include <vector>
#include "ByteCodeInstruction.h"
#include <string>
#include <cstdint>
class VM
{
    private:
        std::string disassembleInstruction(ByteCodeInstruction instruction);
    public:
        std::vector<ByteCodeInstruction> instructions;
        std::vector<int> stack;
        VM(std::vector<ByteCodeInstruction> instructions);
        void run();
        void retrieveOperands(int &a, int &b);
        void disassembleInstruction();
        void dumpByteCode();
};