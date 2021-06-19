#include "../headers/PrintNode.h"
#include "../headers/Visitor.h"
#include "../headers/AstNode.h"
void PrintNode::accept(Visitor& v)
{
    v.visitPrintNode(this);
}

PrintNode::PrintNode(ASTNode* contents) : contents{ contents } {}