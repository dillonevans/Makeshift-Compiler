#include "../headers/BinOpNode.h"
#include "../headers/CompoundStatementNode.h"
#include "../headers/IfStatementNode.h"
#include "../headers/IntNode.h"
#include "../headers/PrintVisitor.h"
#include "../headers/VariableDeclarationNode.h"
#include "../headers/BooleanLiteralNode.h"
#include "../headers/Visitor.h"
#include "../headers/PrintNode.h"
#include "../headers/VariableNode.h"
#include "../headers/FunctionNode.h"
#include "../headers/ReturnNode.h"

#include "../headers/Value.h"
#include <iostream>

void PrintVisitor::visitBinOPNode(BinOpNode &node) 
{
    
}

void PrintVisitor::visitIntNode(IntNode &node) 
{
    
}

void PrintVisitor::visitCompoundStatementNode(CompoundStatementNode &node) 
{
    
}

void PrintVisitor::visitIfStatementNode(IfStatementNode &node) 
{
    
}

void PrintVisitor::visitPrintNode(PrintNode &node) 
{
    
}

void PrintVisitor::visitVariableDeclarationNode(VariableDeclarationNode &node) 
{
    
}

void PrintVisitor::visitBooleanLiteralNode(BooleanLiteralNode &node) 
{
    
}

void PrintVisitor::visitVariableNode(VariableNode &node) 
{
    
}

void PrintVisitor::visitFunctionNode(FunctionNode &node) 
{
    std::cout << node.getFunctionName();
    node.getFunctionBody()->accept(*this);
    return;
}

void PrintVisitor::visitReturnNode(ReturnNode &node) 
{
    
}

void PrintVisitor::visitFunctionCallNode(FunctionCallNode &node) 
{
    
}

void PrintVisitor::visitProgramNode(ProgramNode &node)
{

}