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
    } literals;

public:
    Value(int literal);
    Value(bool literal);
};
#endif