#include "../headers/BooleanLiteralNode.h"
#include "../headers/Visitor.h"
BooleanLiteralNode::BooleanLiteralNode(bool value) : value{value}{}
void BooleanLiteralNode::accept(Visitor &v){
    v.visitBooleanLiteralNode(*this);
}