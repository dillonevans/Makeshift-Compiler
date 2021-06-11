#ifndef ASTNODE_H
#define ASTNODE_H

class Visitor;
class ASTNode
{
    public:
    virtual void accept(Visitor &v) = 0;
    ASTNode* contents;
};
#endif