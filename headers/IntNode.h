#ifndef INTNODE_H
#define INTNODE_H

#include "AstNode.h"

class IntNode : public ASTNode
{
public:
    int value;
    IntNode(int value);
    void accept(Visitor& v);
};
#endif