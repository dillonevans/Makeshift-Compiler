#include "../headers/IntNode.h"
#include "../headers/Visitor.h"
IntNode::IntNode(int value)
{
    this->value = value;
};

void IntNode::accept(Visitor& v)
{
    v.visitIntNode(this);
}