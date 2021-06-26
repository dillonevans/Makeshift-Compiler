#include "../include/IfStatementNode.h"
#include "../include/Visitor.h"
IfStatementNode::IfStatementNode(ASTNode* condition, ASTNode* ifStmtBody, ASTNode* elseBody) : condition{ condition }, ifStmtBody{ ifStmtBody }, elseBody{ elseBody } {}

void IfStatementNode::accept(Visitor& v)
{
    v.visitIfStatementNode(this);
}

ASTNode* IfStatementNode::getIfStmtBody()
{
    return ifStmtBody;
}

ASTNode* IfStatementNode::getCondition()
{
    return condition;
}

ASTNode* IfStatementNode::getElseBody()
{
    return elseBody;
}
