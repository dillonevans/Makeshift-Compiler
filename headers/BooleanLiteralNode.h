#ifndef BOOLNODE_H
#define BOOLNODE_H

#include "AstNode.h"

class BooleanLiteralNode : public ASTNode
{
    public: 
    bool value;
    BooleanLiteralNode(bool value);
    void accept(Visitor &v);
};
#endif