#include "../headers/CompoundStatementNode.h"
#include "../headers/Visitor.h"

/**
 * Returns a list of statements contained within the block
 */
std::vector<ASTNode*> CompoundStatementNode::getStatements()
{
    return statements;
}

/**
 * Constructor
 */
CompoundStatementNode::CompoundStatementNode(std::vector<ASTNode*> list) : statements{ list } {};

void CompoundStatementNode::accept(Visitor& v)
{
    v.visitCompoundStatementNode(this);
}
