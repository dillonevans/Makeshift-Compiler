#ifndef PRINTNODE_H
#define PRINTNODE_H
#include "AstNode.h"

class PrintNode : public ASTNode
{
public:
    void accept(Visitor& v);
    ASTNode* contents;
    PrintNode(ASTNode* contents);
};

#endif