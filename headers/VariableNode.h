#ifndef VARNODE_H
#define VARNODE_H

#include "AstNode.h"
#include "Value.h"

class VariableNode : public ASTNode
{
    public: 
    Type type;
    std::string identifier;
    VariableNode(Type type, std::string identifer);
    void accept(Visitor &v);
};
#endif