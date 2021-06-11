#include "../headers/BinOpNode.h"
#include "../headers/Visitor.h"
BinOpNode::BinOpNode(ASTNode *left, OperatorType op, ASTNode *right)
{
    this->left = left;
    this->op = op;
    this->right = right;
}

void BinOpNode::accept(Visitor &v)
{
    v.visitBinOPNode(*this);
}