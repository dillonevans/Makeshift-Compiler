#include "../headers/AssignmentNode.h"
#include "../headers/Visitor.h"

AssignmentNode::AssignmentNode(ASTNode* lhs, ASTNode* rhs)
{
    this->lhs = lhs;
    this->rhs = rhs;
}

void AssignmentNode::accept(Visitor& v)
{
    v.visitAssignmentNode(this);
}