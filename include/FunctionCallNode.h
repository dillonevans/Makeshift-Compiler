#ifndef FUNC_CALL_NODE_H
#define FUNC_CALL_NODE_H

#include "AstNode.h"
#include <string>
#include <vector>
class FunctionCallNode : public ASTNode
{
private:
    std::string identifier;
public:
    std::string getIdentifier();
    std::vector<ASTNode*> arguments;
    FunctionCallNode(std::string identifier, std::vector<ASTNode*> args);
    void accept(Visitor& v);
};
#endif