#ifndef BIN_OP_NODE_H
#define BIN_OP_NODE_H

#include "AstNode.h"

enum BinaryOperatorType
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
    LogicalOrOperator,
    AssignmentOperator,
    EqualsOperator
};
class BinaryOperatorNode : public ASTNode
{
public:
    ASTNode* left, * right;
    BinaryOperatorType op;
    BinaryOperatorNode(ASTNode* left, BinaryOperatorType op, ASTNode* right);
    void accept(Visitor& v);
};

#endif