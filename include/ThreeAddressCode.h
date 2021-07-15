#ifndef __THREEADDRESSCODE_H__
#define __THREEADDRESSCODE_H__
#include <string>
struct ThreeAddressCode
{
    std::string op, arg1, arg2, result;

    ThreeAddressCode(std::string op, std::string arg1, std::string arg2, std::string result)
    {
        this->op = op;
        this->arg1 = arg1;
        this->arg2 = arg2;
        this->result = result;
    }
};
#endif // __THREEADDRESSCODE_H__