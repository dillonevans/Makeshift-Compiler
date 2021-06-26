#ifndef PROGRAM_NODE_H
#define PROGRAM_NODE_H

#include <vector>
#include <unordered_map>
#include "AstNode.h"

class ProgramNode : public ASTNode
{
private:
    std::vector<ASTNode*> programUnits;

public:
    void accept(Visitor& v);
    std::vector<ASTNode*> getProgramUnits();
    ProgramNode(std::vector<ASTNode*> list);
    std::unordered_map<std::string, int> stringLiterals;
};

#endif