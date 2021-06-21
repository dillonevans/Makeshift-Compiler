#include "../headers/VariableDeclarationNode.h"
#include "../headers/Visitor.h"

VariableDeclarationNode::VariableDeclarationNode(ASTNode* varNode, ASTNode* rhs, std::string identifier)
{
    this->varNode = varNode;
    this->rhs = rhs;
    this->identifier = identifier;
}

void VariableDeclarationNode::accept(Visitor& v)
{
    v.visitVariableDeclarationNode(this);
}

ASTNode* VariableDeclarationNode::getRHS()
{
    return this->rhs;
}

Type VariableDeclarationNode::getType()
{
    return this->type;
}

std::string VariableDeclarationNode::getIdentifier()
{
    return this->identifier;
}

ASTNode* VariableDeclarationNode::getVarNode()
{
    return this->varNode;
}