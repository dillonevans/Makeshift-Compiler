#ifndef UNARY_OP_NODE_H
#define UNARY_OP_NODE_H

#include "AstNode.h"

enum UnaryOperatorType
{
    UnaryMinusOperator,
    PreIncrementOperator,
    PostIncrementOperator,
    PreDecrementOperator,
    PostDecrementOperator
};
class UnaryOperatorNode : public ASTNode
{
public:
    ASTNode* child;
    UnaryOperatorType op;
    UnaryOperatorNode(UnaryOperatorType op, ASTNode* child);
    void accept(Visitor& v);
};

#endif