#ifndef VDN_H
#define VDN_H

#include "AstNode.h"
#include <string>
#include "Value.h"
#include "VariableNode.h"
class VariableDeclarationNode : public ASTNode
{

private:
    ASTNode* rhs;
    std::string identifier;
    VariableNode* varNode;
    Type type;

public:
    ASTNode* getRHS();
    Type getType();
    std::string getIdentifier();
    VariableNode* getVarNode();

    VariableDeclarationNode(VariableNode* varNode, ASTNode* rhs, std::string identifier);
    void accept(Visitor& v);
};

#endif