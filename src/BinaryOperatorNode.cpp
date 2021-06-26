#include "../include/BinaryOperatorNode.h"
#include "../include/Visitor.h"
BinaryOperatorNode::BinaryOperatorNode(ASTNode* left, OperatorType op, ASTNode* right)
{
    this->left = left;
    this->op = op;
    this->right = right;
}

void BinaryOperatorNode::accept(Visitor& v)
{
    v.visitBinaryOperatorNode(this);
}