#include "../headers/FunctionNode.h"
#include "../headers/Visitor.h"

std::vector<VariableNode*> FunctionNode::getParameterList() 
{
    return this->parameterList;
}

Type FunctionNode::getReturnType() 
{
    return this->returnType;
}

ASTNode* FunctionNode::getFunctionBody()
{
    return this->functionBody;
}

void FunctionNode::accept(Visitor &v) 
{
    v.visitFunctionNode(*this);
}

FunctionNode::FunctionNode(std::string functionName, Type returnType, std::vector<VariableNode*> parameterList, ASTNode* functionBody) 
{
    this->functionName = functionName;
    this->returnType = returnType;
    this->parameterList = parameterList;
    this->functionBody = functionBody;
}

FunctionNode::FunctionNode(Type returnType) 
{
    this->returnType = returnType;
}

std::string FunctionNode::getFunctionName(){
    return this->functionName;
}