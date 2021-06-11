#ifndef BINOPNODE_H
#define BINOPNODE_H

#include "AstNode.h"

enum OperatorType 
{
    AdditionOperator, 
    SubtractionOperator, 
    MultiplicationOperator, 
    DivisionOperator,
    LessThanOperator,
    LessThanOrEqualToOperator,
    GreaterThanOperator,
    GreaterThanOrEqualToOperator,
    LogicalAndOperator,
    LogicalOrOperator
};
class BinOpNode : public ASTNode
{
    public:
    ASTNode *left, *right;
    OperatorType op;
    BinOpNode(ASTNode *left, OperatorType op, ASTNode *right);
    void accept(Visitor &v);
};

#endif