#include "../include/StringLiteralNode.h"
#include "../include/Visitor.h"
StringLiteralNode::StringLiteralNode(std::string value)
{
    this->value = value;
};

void StringLiteralNode::accept(Visitor& v)
{
    v.visitStringLiteralNode(this);
}