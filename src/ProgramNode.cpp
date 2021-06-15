#include "../headers/ProgramNode.h"
#include "../headers/Visitor.h"

std::vector<ASTNode*> ProgramNode::getProgramUnits(){return programUnits;}
ProgramNode::ProgramNode(std::vector<ASTNode*> list) : programUnits{list} {};
void ProgramNode::accept(Visitor &v){v.visitProgramNode(*this);}
