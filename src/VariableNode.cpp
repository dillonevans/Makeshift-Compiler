#include "../headers/VariableNode.h"
#include "../headers/Visitor.h"
VariableNode::VariableNode(Type type, std::string identifier)
{
    this->type = type;
    this->identifier = identifier;
};

void VariableNode::accept(Visitor &v)
{
    v.visitVariableNode(*this);
}