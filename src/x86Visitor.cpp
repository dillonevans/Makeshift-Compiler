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
  
    switch(node->op)
    {
        case AdditionOperator:
            reg l, r;
            node->left->accept(*this);
            l = this->allocatedRegister;
            node->right->accept(*this);
            r = this->allocatedRegister;
            std::cout << "addq " << registerMap[l].first << ", " <<  registerMap[r].first << "\n" ;
            allocatedRegister = r;
            freeRegister(l);
            break;
    }
};

void x86Visitor::visitIntNode(IntNode* node)
{
    reg store = allocateRegister();
    std::cout << "movq $" << node->value << ", " << registerMap[store].first << "\n";
    this->allocatedRegister = store;
}

void x86Visitor::visitCompoundStatementNode(CompoundStatementNode* node)
{
    for (const auto& statement : node->getStatements())
    {
        statement->accept(*this);
    }
}

void x86Visitor::visitIfStatementNode(IfStatementNode* node)
{

}

void x86Visitor::visitPrintNode(PrintNode* node)
{
    node->contents->accept(*this);
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
    std::cout << node->getFunctionName() << ":\n";
    std::cout << "push %rbp \t\t# save the base pointer\n"
                 "movq %rsp, %rbp \t# set new base pointer\n\n";
    node->getFunctionBody()->accept(*this);

    
    std::cout << "\npushq %rbx \t\t# save callee-saved registers\n"
    "pushq %r12\n"
    "pushq %r13\n"
    "pushq %r14\n"
    "pushq %r15\n\n"
    "movq %rbp, %rsp \t# reset stack to base pointer.\n"
    "popq %rbp \t\t# restore the old base pointer\n"
    "ret \t\t\t# return to caller\n";
}

void x86Visitor::visitFunctionCallNode(FunctionCallNode* node)
{
    
}

void x86Visitor::visitProgramNode(ProgramNode* node)
{
    for (const auto& programUnit : node->getProgramUnits())
    {
        programUnit->accept(*this);
    }
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
    for (int i = 0; i < registerMap.size(); i++)
    {
        if (!registerMap[i].second) 
        { 
            registerMap[registerNumber].second = true; 
            return i; 
        }
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
