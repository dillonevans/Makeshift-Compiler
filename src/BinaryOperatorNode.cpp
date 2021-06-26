#include "../headers/BinaryOperatorNode.h"
#include "../headers/Visitor.h"
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