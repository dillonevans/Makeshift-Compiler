#ifndef FUNC_CALL_NODE_H
#define FUNC_CALL_NODE_H

#include "AstNode.h"
#include <string>
class FunctionCallNode : public ASTNode
{
private:
    std::string identifier;
public:
    std::string getIdentifier();
    FunctionCallNode(std::string identifier);
    void accept(Visitor& v);
};
#endif