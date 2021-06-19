#ifndef VARNODE_H
#define VARNODE_H

#include "AstNode.h"
#include "Value.h"

class VariableNode : public ASTNode
{
private:
    std::string identifier;
    Type type;
public:
    Type getType();
    std::string getIdentifier();
    void setType(Type type);
    VariableNode(Type type, std::string identifer);
    void accept(Visitor& v);
};
#endif