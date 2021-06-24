#include "../headers/StringLiteralNode.h"
#include "../headers/Visitor.h"
StringLiteralNode::StringLiteralNode(std::string value)
{
    this->value = value;
};

void StringLiteralNode::accept(Visitor& v)
{
    v.visitStringLiteralNode(this);
}