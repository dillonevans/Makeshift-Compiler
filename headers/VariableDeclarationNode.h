#ifndef VDN_H
#define VDN_H

#include "AstNode.h"
#include <string>
#include "Value.h"

class VariableDeclarationNode : public ASTNode
{
    public:
    ASTNode *rhs;
    Type type;
    std::string identifier;
    
    VariableDeclarationNode(Type type, std::string identifier, ASTNode *rhs);
    void accept(Visitor &v);
};

#endif