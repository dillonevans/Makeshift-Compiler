#ifndef FUNCNODE_H
#define FUNCNODE_H

#include "AstNode.h"
#include "Value.h"
#include "VariableNode.h"
#include <vector>
#include <string>
#include "CompoundStatementNode.h"
class FunctionNode : public ASTNode
{
    private:
    std::vector<VariableNode*> parameterList;
    ASTNode* functionBody;
    Type returnType;
    std::string functionName;
 
    public: 
    FunctionNode(Type returnType);
    FunctionNode(std::string functionName, Type returnType, std::vector<VariableNode*> parameterList, ASTNode* functionBody);
    ASTNode* getFunctionBody();
    std::vector<VariableNode*> getParameterList();
    Type getReturnType();
    void accept(Visitor &v);
    std::string getFunctionName();

};




#endif