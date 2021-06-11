#include "../headers/VariableDeclarationNode.h"
#include "../headers/Visitor.h"

VariableDeclarationNode::VariableDeclarationNode(VariableNode* varNode, ASTNode *rhs)
{
    this->varNode = varNode;
    this->rhs = rhs;
}

void VariableDeclarationNode::accept(Visitor &v)
{
    v.visitVariableDeclarationNode(*this);
}