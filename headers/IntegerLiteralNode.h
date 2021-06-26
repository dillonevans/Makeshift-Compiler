#ifndef INTNODE_H
#define INTNODE_H

#include "AstNode.h"

class IntegerLiteralNode : public ASTNode
{
public:
    int value;
    IntegerLiteralNode(int value);
    void accept(Visitor& v);
};
#endif