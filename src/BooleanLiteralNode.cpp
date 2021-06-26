#include "../include/BooleanLiteralNode.h"
#include "../include/Visitor.h"
BooleanLiteralNode::BooleanLiteralNode(bool value) : value{ value } {}
void BooleanLiteralNode::accept(Visitor& v)
{
    v.visitBooleanLiteralNode(this);
}