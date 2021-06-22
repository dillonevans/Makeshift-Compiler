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
#include "../headers/FunctionCallNode.h"
#include <iostream>

void x86Visitor::visitBinOPNode(BinOpNode* node)
{

    reg l, r;
    switch (node->op)
    {
        case AdditionOperator:
            node->left->accept(*this);
            l = this->allocatedRegister;
            node->right->accept(*this);
            r = this->allocatedRegister;
            std::cout << "add " << registerMap[l].first << ", " << registerMap[r].first << "\n";
            allocatedRegister = r;
            freeRegister(l);
            break;
        case AssignmentOperator:

            if (node->left)
            {
                node->left->accept(*this);

            }
            if (node->right)
            {
                isAssignment = true;
                node->right->accept(*this);
                r = this->allocatedRegister;
                isAssignment = false;
            }
            std::cout << "movq " << registerMap[r].first << ", " << this->variableName << "\n";


            break;
        case LessThanOperator:
        case LessThanOrEqualToOperator:
        case GreaterThanOperator:
        case GreaterThanOrEqualToOperator:
            break;
    }
};

void x86Visitor::visitIntNode(IntNode* node)
{
    reg store = allocateRegister();
    std::cout << "movq $" << node->value << ", " << registerMap[store].first << "\t\t# store " << node->value << " in " << registerMap[store].first << "\n";
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
    int elseLabel = allocateLabel(), endIfLabel = allocateLabel();
    node->getCondition()->accept(*this);
}

void x86Visitor::visitPrintNode(PrintNode* node)
{
    node->contents->accept(*this);
}


void x86Visitor::visitBooleanLiteralNode(BooleanLiteralNode* node)
{

}

void x86Visitor::visitReturnNode(ReturnNode* node)
{

}

void x86Visitor::visitFunctionNode(FunctionNode* node)
{
    scope++;
    std::string label = node->getFunctionName() == "main" ? "start" : node->getFunctionName();
    std::cout << "\n_" << label << ":\n";
    std::cout << "pushq %rbp \t\t# save the base pointer\nmovq %rsp, %rbp \t# set new base pointer\n\n";
    std::cout << "subq " << node->stackOffset << " %rsp\n";
    node->getFunctionBody()->accept(*this);

    std::cout << "\npushq %rbx \t\t# save callee-saved registers\n"
        "pushq %r12\n"
        "pushq %r13\n"
        "pushq %r14\n"
        "pushq %r15\n\n"
        "movq %rbp, %rsp \t# reset stack to base pointer.\n"
        "popq %rbp \t\t# restore the old base pointer\n"
        "ret \t\t\t# return to caller\n";
    scope--;
    while (locals.size() > 0)
    {
        locals.pop_back();
    }
    scope--;
}



void x86Visitor::visitFunctionCallNode(FunctionCallNode* node)
{
    std::cout << "call _" << node->getIdentifier() << "\n";
}

void x86Visitor::visitProgramNode(ProgramNode* node)
{
    std::cout << "global _start\n";
    std::cout << "section .data:\n";
    std::cout << "section .text:\n";
    for (const auto& programUnit : node->getProgramUnits())
    {
        programUnit->accept(*this);
    }
}

void x86Visitor::visitWhileNode(WhileNode* node)
{

}

int x86Visitor::allocateRegister()
{
    for (int i = 0; i < registerMap.size(); i++)
    {
        if (!registerMap[i].second)
        {
            registerMap[i].second = true;
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

void x86Visitor::visitVariableDeclarationNode(VariableDeclarationNode* node)
{
    localOffset -= 4;
    locals.push_back(Local(node->getIdentifier(), scope, localOffset));
    node->getRHS()->accept(*this);
    std::cout << "movq " << registerMap[this->allocatedRegister].first << " " << localOffset << "(%rbp)\n";
    freeRegister(this->allocatedRegister);
}

int x86Visitor::resolveLocal(std::string identifier)
{
    for (int i = locals.size() - 1; i >= 0; i--)
    {
        if (identifier == locals[i].getIdentifier())
        {
            return locals[i].localOffset;
        }
    }
    return -1;
}

void x86Visitor::visitVariableNode(VariableNode* node)
{
    int offset = resolveLocal(node->getIdentifier());
    if (!isAssignment)
    {
        reg store = allocateRegister();
        std::cout << "movq " << offset << "(%rbp) " << registerMap[store].first << "\n";
        this->allocatedRegister = store;
    }
    else
    {
    }
    this->variableName = std::to_string(offset) + "(%rbp)";
    return;
}
