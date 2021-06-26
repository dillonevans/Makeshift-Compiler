#include "../include/WhileNode.h"
#include "../include/Visitor.h"

WhileNode::WhileNode(ASTNode* condition, ASTNode* body)
{
    this->condition = condition;
    this->body = body;
}

ASTNode* WhileNode::getCondition()
{
    return this->condition;
}

ASTNode* WhileNode::getBody()
{
    return this->body;
}

void WhileNode::accept(Visitor& v)
{
    v.visitWhileNode(this);
}