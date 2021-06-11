#include "../headers/VariableDeclarationNode.h"
#include "../headers/Visitor.h"

VariableDeclarationNode::VariableDeclarationNode(Type type, std::string identifier, ASTNode *rhs): type{type}, identifier{identifier}
{
    this->rhs = rhs;
}

void VariableDeclarationNode::accept(Visitor &v)
{
    v.visitVariableDeclarationNode(*this);
}