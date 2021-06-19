#include "../headers/FunctionCallNode.h"
#include "../headers/Visitor.h"
FunctionCallNode::FunctionCallNode(std::string identifier)
{
    this->identifier = identifier;
};

void FunctionCallNode::accept(Visitor& v)
{
    v.visitFunctionCallNode(this);
}
std::string FunctionCallNode::getIdentifier()
{
    return this->identifier;
}
