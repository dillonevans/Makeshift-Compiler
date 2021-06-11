#ifndef VALUE_H
#define VALUE_H

#include <string>

enum Type
{
    IntegerPrimitive,
    BooleanPrimitive,
    ImplicitVarType
};

class Value
{
    union
    {
        int intLiteral;
        bool boolLiteral;
        double doubleLiteral;
        std::string stringLiteral;

    } literals;

    public:
    Value(int literal);
    Value(bool literal);
};
#endif