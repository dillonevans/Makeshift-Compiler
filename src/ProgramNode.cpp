#include "../include/ProgramNode.h"
#include "../include/Visitor.h"

ProgramNode::ProgramNode(std::vector<ASTNode*> list) : programUnits{ list } {};

std::vector<ASTNode*> ProgramNode::getProgramUnits()
{
    return programUnits;
}

void ProgramNode::accept(Visitor& v)
{
    v.visitProgramNode(this);
}
