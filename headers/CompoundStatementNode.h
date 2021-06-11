#ifndef COMPOUNDSTMTNODE_H
#define COMPOUNDSTMTNODE_H

#include <vector>
#include "AstNode.h"

class CompoundStatementNode : public ASTNode
{
    private:
    std::vector<ASTNode*> statements;
    
    public:
    void accept(Visitor &v);
    std::vector<ASTNode*> getStatements();
    CompoundStatementNode(std::vector<ASTNode*> list);
  
};

#endif