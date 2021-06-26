#include "../headers/FunctionDeclarationNode.h"
#include "../headers/Visitor.h"

std::vector<std::pair<VariableDeclarationNode*, Type>> FunctionDeclarationNode::getParameterList()
{
    return this->parameterList;
}

Type FunctionDeclarationNode::getReturnType()
{
    return this->returnType;
}

ASTNode* FunctionDeclarationNode::getFunctionBody()
{
    return this->functionBody;
}

void FunctionDeclarationNode::accept(Visitor& v)
{
    v.visitFunctionDeclarationNode(this);
}

FunctionDeclarationNode::FunctionDeclarationNode(std::string functionName, Type returnType, std::vector<std::pair<VariableDeclarationNode*, Type>> parameterList, ASTNode* functionBody)
{
    this->functionName = functionName;
    this->returnType = returnType;
    this->parameterList = parameterList;
    this->functionBody = functionBody;
}

FunctionDeclarationNode::FunctionDeclarationNode(Type returnType, std::string functionName)
{
    this->returnType = returnType;
    this->functionName = functionName;
}

std::string FunctionDeclarationNode::getFunctionName()
{
    return this->functionName;
}

int FunctionDeclarationNode::getParameterCount()
{
    return this->parameterCount;
}