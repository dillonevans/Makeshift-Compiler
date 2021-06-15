#ifndef RETNODE_H
#define RETNODE_H

#include "AstNode.h"
#include "Value.h"
#include "FunctionNode.h"
class ReturnNode : public ASTNode
{
    public: 
    ASTNode* toReturn;
    ReturnNode(ASTNode *toReturn);
    void accept(Visitor &v);
};
#endif