#ifndef ASSIGNMENT_NODE_H
#define ASSIGNMENT_NODE_H
#include "AstNode.h"

class AssignmentNode : public ASTNode
{
public:
    void accept(Visitor& v);
    ASTNode* lhs, * rhs;
    AssignmentNode(ASTNode* lhs, ASTNode* rhs);
};

#endif