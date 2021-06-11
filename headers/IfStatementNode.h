#ifndef IFNODE_H
#define IFNODE_H

#include "AstNode.h"

class IfStatementNode : public ASTNode
{
    private:
    ASTNode* condition, *ifStmtBody, *elseBody;
    
    public: 
    IfStatementNode(ASTNode* condition, ASTNode *ifStmtBody, ASTNode *elseBody);
    ASTNode* getIfStmtBody();
    ASTNode* getCondition();
    ASTNode* getElseBody();
    void accept(Visitor &v);

};

#endif