#include "../headers/CompoundStatementNode.h"
#include "../headers/Visitor.h"

std::vector<ASTNode*> CompoundStatementNode::getStatements(){return statements;}
CompoundStatementNode::CompoundStatementNode(std::vector<ASTNode*> list) : statements{list} {};
void CompoundStatementNode::accept(Visitor &v){v.visitCompoundStatementNode(*this);}
