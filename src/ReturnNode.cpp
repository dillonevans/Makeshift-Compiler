#include "../headers/ReturnNode.h"
#include "../headers/Visitor.h"
ReturnNode::ReturnNode(ASTNode* toReturn)
{
    this->toReturn = toReturn;
};

void ReturnNode::accept(Visitor& v)
{
    v.visitReturnNode(this);
}