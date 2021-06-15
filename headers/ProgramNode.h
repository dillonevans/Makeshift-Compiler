#ifndef PROGRAM_NODE_H
#define PROGRAM_NODE_H

#include <vector>
#include "AstNode.h"

class ProgramNode : public ASTNode
{
    private:
    std::vector<ASTNode*> programUnits;
    
    public:
    void accept(Visitor &v);
    std::vector<ASTNode*> getProgramUnits();
    ProgramNode(std::vector<ASTNode*> list);
};

#endif