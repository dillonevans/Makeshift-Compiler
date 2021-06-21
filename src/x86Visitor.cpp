#include "../headers/x86Visitor.h"


#include "../headers/BinOpNode.h"
#include "../headers/CompoundStatementNode.h"
#include "../headers/IfStatementNode.h"
#include "../headers/IntNode.h"
#include "../headers/VariableDeclarationNode.h"
#include "../headers/BooleanLiteralNode.h"
#include "../headers/Visitor.h"
#include "../headers/PrintNode.h"
#include "../headers/VariableNode.h"
#include "../headers/FunctionNode.h"
#include "../headers/ReturnNode.h"
#include "../headers/ProgramNode.h"
#include "../headers/Value.h"
#include <iostream>

void x86Visitor::visitBinOPNode(BinOpNode* node)
{
    if (node->left) { node->left->accept(*this); }
    if (node->right) { node->right->accept(*this); }
};

void x86Visitor::visitIntNode(IntNode* node)
{

}

void x86Visitor::visitCompoundStatementNode(CompoundStatementNode* node)
{

}

void x86Visitor::visitIfStatementNode(IfStatementNode* node)
{

}

void x86Visitor::visitPrintNode(PrintNode* node)
{

}

void x86Visitor::visitVariableNode(VariableNode* node)
{

}

void x86Visitor::visitVariableDeclarationNode(VariableDeclarationNode* node)
{

}

void x86Visitor::visitBooleanLiteralNode(BooleanLiteralNode* node)
{

}

void x86Visitor::visitReturnNode(ReturnNode* node)
{

}

void x86Visitor::visitFunctionNode(FunctionNode* node)
{

}

void x86Visitor::visitFunctionCallNode(FunctionCallNode* node)
{

}

void x86Visitor::visitProgramNode(ProgramNode* node)
{

}

void x86Visitor::visitWhileNode(WhileNode* node)
{

}

void x86Visitor::visitAssignmentNode(AssignmentNode* node)
{

}
int x86Visitor::allocateRegister()
{
    int registerNumber = 0;
    for (auto& x : registerMap)
    {
        if (!x.second.second) { return registerCount; }
        registerNumber++;
    }
    return -1;
}

int x86Visitor::allocateLabel()
{
    return labelCount++;
}

void x86Visitor::freeRegister(int reg)
{
    registerMap[reg].second = false;
}
