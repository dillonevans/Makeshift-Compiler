#include "../headers/VariableNode.h"
#include "../headers/Visitor.h"
VariableNode::VariableNode(Type type, std::string identifier)
{
    this->type = type;
    this->identifier = identifier;
};

void VariableNode::accept(Visitor& v)
{
    v.visitVariableNode(this);
}

Type VariableNode::getType()
{
    return this->type;
}

std::string VariableNode::getIdentifier()
{
    return this->identifier;
}

void VariableNode::setType(Type type)
{
    this->type = type;
}
