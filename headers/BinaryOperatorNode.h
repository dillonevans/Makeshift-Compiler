#ifndef BIN_OP_NODE_H
#define BIN_OP_NODE_H

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
    LogicalOrOperator,
    AssignmentOperator,
    EqualsOperator
};
class BinaryOperatorNode : public ASTNode
{
public:
    ASTNode* left, * right;
    OperatorType op;
    BinaryOperatorNode(ASTNode* left, OperatorType op, ASTNode* right);
    void accept(Visitor& v);
};

#endif