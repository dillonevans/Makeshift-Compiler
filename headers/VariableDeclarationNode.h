#ifndef VDN_H
#define VDN_H

#include "AstNode.h"
#include <string>
#include "Value.h"
#include "VariableNode.h"
class VariableDeclarationNode : public ASTNode
{
    public:
    ASTNode *rhs;
    Type type;
    std::string identifier;
    VariableNode *varNode;
    
    VariableDeclarationNode(VariableNode *varNode, ASTNode *rhs);
    void accept(Visitor &v);
};

#endif