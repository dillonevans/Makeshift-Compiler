#ifndef VARNODE_H
#define VARNODE_H

#include "AstNode.h"
#include "Type.h"

class VariableNode : public ASTNode
{
private:
    std::string identifier;
    Type type;
    bool isLocal;

public:
    Type getType();
    std::string getIdentifier();
    void setType(Type type);
    VariableNode(Type type, std::string identifer, bool isLocal);
    void accept(Visitor& v);
};
#endif