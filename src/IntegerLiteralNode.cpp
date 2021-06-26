#include "../headers/IntegerLiteralNode.h"
#include "../headers/Visitor.h"
IntegerLiteralNode::IntegerLiteralNode(int value)
{
    this->value = value;
};

void IntegerLiteralNode::accept(Visitor& v)
{
    v.visitIntegerLiteralNode(this);
}