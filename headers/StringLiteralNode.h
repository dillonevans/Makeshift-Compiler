#ifndef STRING_LITERAL_NODE_H
#define STRING_LITERAL_NODE_H

#include "AstNode.h"
#include <string>
class StringLiteralNode : public ASTNode
{
public:
    std::string value;
    StringLiteralNode(std::string value);
    void accept(Visitor& v);
};
#endif