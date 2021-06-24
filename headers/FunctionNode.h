#ifndef FUNCNODE_H
#define FUNCNODE_H

#include "AstNode.h"
#include "Type.h"
#include "VariableDeclarationNode.h"
#include <vector>
#include <string>
#include "CompoundStatementNode.h"
class FunctionNode : public ASTNode
{
private:
    int parameterCount;
public:
    FunctionNode(Type returnType);
    FunctionNode(std::string functionName, Type returnType, std::vector<std::pair<VariableDeclarationNode*, Type>> parameterList, ASTNode* functionBody);
    ASTNode* getFunctionBody();
    std::vector<std::pair<VariableDeclarationNode*, Type>> getParameterList();
    Type getReturnType();
    void accept(Visitor& v);
    std::string getFunctionName();
    int getParameterCount();
    std::vector<std::pair<VariableDeclarationNode*, Type>> parameterList;
    ASTNode* functionBody;
    Type returnType;
    std::string functionName;
    int stackOffset = 0;

};




#endif