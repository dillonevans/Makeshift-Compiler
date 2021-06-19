#ifndef WHILE_NODE_H
#define WHILE_NODE_H

#include "AstNode.h"

class WhileNode : public ASTNode
{
private:
    ASTNode* condition, * body;

public:
    WhileNode(ASTNode* condition, ASTNode* body);
    ASTNode* getCondition();
    ASTNode* getBody();
    void accept(Visitor& v);
};
#endif