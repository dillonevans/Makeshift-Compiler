#include "../include/GenTACVisitor.h"


#include "../include/BinaryOperatorNode.h"
#include "../include/CompoundStatementNode.h"
#include "../include/IfStatementNode.h"
#include "../include/IntegerLiteralNode.h"
#include "../include/VariableDeclarationNode.h"
#include "../include/BooleanLiteralNode.h"
#include "../include/Visitor.h"
#include "../include/VariableNode.h"
#include "../include/FunctionDeclarationNode.h"
#include "../include/ReturnNode.h"
#include "../include/ProgramNode.h"
#include "../include/Type.h"
#include "../include/FunctionCallNode.h"
#include "../include/StringSymbolTable.h"
#include "../include/StringLiteralNode.h"
#include <iostream>

void GenTACVisitor::visitBinaryOperatorNode(BinaryOperatorNode* node)
{
    int l, r;
    std::string lName, rName;
    switch (node->op)
    {
        case AdditionOperator:
            node->left->accept(*this);
            l = this->allocatedRegister;
            lName = this->currentName;

            node->right->accept(*this);
            r = this->allocatedRegister;
            rName = this->currentName;

            //std::cout << "\taddq t" << l << ", t" << r << "\n";
            this->currentName = "t" + std::to_string(allocateRegister());
            std::cout << "addq " << lName << "," << currentName << "\n";
            this->allocatedRegister = r;
            break;
        case SubtractionOperator:
            node->left->accept(*this);
            l = this->allocatedRegister;
            lName = this->currentName;

            node->right->accept(*this);
            r = this->allocatedRegister;
            rName = this->currentName;

            //std::cout << "\taddq t" << l << ", t" << r << "\n";
            this->currentName = "t" + std::to_string(allocateRegister());
            std::cout << currentName << " = " << lName << " - " << rName << "\n";
            this->allocatedRegister = r;
            break;
        case MultiplicationOperator:
            node->left->accept(*this);
            lName = this->currentName;
            l = this->allocatedRegister;
            node->right->accept(*this);
            r = this->allocatedRegister;
            rName = this->currentName;
            this->currentName = "t" + std::to_string(allocateRegister());
            std::cout << currentName << " = " << lName << " * " << rName << "\n";
            this->allocatedRegister = r;
            break;
        case AssignmentOperator:
            //Loads the result into the register
            if (node->left)
            {
                node->left->accept(*this);
                l = this->allocatedRegister;
                lName = this->currentName;

            }
            //This moves the result from the register into the variable's location
            if (node->right)
            {
                isAssignment = true;
                node->right->accept(*this);
                isAssignment = false;
            }
            std::cout << "movq " << lName << ", " << variableName << "\n";
            break;
        case LessThanOperator:
        case LessThanOrEqualToOperator:
        case GreaterThanOperator:
        case GreaterThanOrEqualToOperator:
        case EqualsOperator:
            node->left->accept(*this);
            l = this->allocatedRegister;
            node->right->accept(*this);
            r = this->allocatedRegister;
            std::string instruction = invertInstruction(node);
            std::cout << "\tcmpq t" << r << ", t" << l << "\n";
            std::cout << "\t" << instruction << " .L" << this->currentLabel << "\n";
            break;
    }
};

void GenTACVisitor::visitIntegerLiteralNode(IntegerLiteralNode* node)
{
    //int store = allocateRegister();
    //std::cout << "t" << store << " = " << node->value << "\n";
    //this->allocatedRegister = store;
    this->currentName = "$" + std::to_string(node->value);
}

void GenTACVisitor::visitCompoundStatementNode(CompoundStatementNode* node)
{
    scope++;
    for (const auto& statement : node->getStatements())
    {
        statement->accept(*this);
    }
    scope--;

    /**
     * Once we leave the innter scope, we pop all the locals associated with it
     * as they are no longer visible to the outer scope
     */
    while (locals.size() > 0 && locals.back().getScope() > scope)
    {
        locals.pop_back();
    }
}

void GenTACVisitor::visitIfStatementNode(IfStatementNode* node)
{
    int endIfLabel = allocateLabel(), elseLabel = allocateLabel();
    this->currentLabel = elseLabel;

    //Generate x86-64 assembly for the condition
    node->getCondition()->accept(*this);
    freeAllRegisters();

    //Generate x86-64 assembly for the body of the if statement
    node->getIfStmtBody()->accept(*this);
    freeAllRegisters();

    //If the condition is true, jump to the end of the if statement
    jumpToLabel(endIfLabel);


    printLabel(elseLabel);
    if (node->getElseBody())
    {
        node->getElseBody()->accept(*this);
    }
    printLabel(endIfLabel);
}

void GenTACVisitor::visitBooleanLiteralNode(BooleanLiteralNode* node)
{

}

void GenTACVisitor::visitReturnNode(ReturnNode* node)
{
    // std::cout << "END FUNCITON LABEL: " << this->endFunctionLabel << "\n";

 //Generate the code for the return value
    node->toReturn->accept(*this);
    //Move the result into rax
    std::cout << "\tmovq " << this->allocatedRegister << ", " << "%rax" << "\t\t# store the return value into %rax\n";
    jumpToLabel(this->endFunctionLabel);
}

void GenTACVisitor::visitFunctionDeclarationNode(FunctionDeclarationNode* node)
{
    scope++;
    Type argType;
    this->endFunctionLabel = allocateLabel();

    std::string label = node->getFunctionName();
    std::cout << "\n" << label << ":\n";
    std::cout << "\tpushq %rbp \t\t# save the base pointer\n\tmovq %rsp, %rbp \t# set new base pointer\n\n";
    std::cout << "\tsubq $" << node->stackOffset << ", %rsp\n";

    std::cout << "\n\tpushq %rbx \t\t# save callee-saved registers\n"
        "\tpushq %r12\n"
        "\tpushq %r13\n"
        "\tpushq %r14\n"
        "\tpushq %r15\n\n";
    int index = 0;
    for (auto& parameter : node->parameterList)
    {
        parameter.first->accept(*this);
        //std::cout << "\tmovq " << argumentRegisters[index++] << ", " << (localOffset) << "(%rbp)\n";
    }

    node->getFunctionBody()->accept(*this);

    printLabel(endFunctionLabel);

    std::cout << "\n\tpopq %r15 \t\t# restore callee-saved registers\n"
        "\tpopq %r14\n"
        "\tpopq %r13\n"
        "\tpopq %r12\n"
        "\tpopq %rbx\n"
        "\n\tmovq %rbp, %rsp\t\t# reset stack to base pointer.\n"
        "\tpopq %rbp \t\t# restore the old base pointer\n"
        "\tret\t\t\t# return to caller\n";


    while (locals.size() > 0)
    {
        locals.pop_back();
    }
    scope--;
    //localOffset = 0;
}

void GenTACVisitor::visitFunctionCallNode(FunctionCallNode* node)
{
    std::cout << "\tpushq %r10\n\tpushq %r11\n";

    for (int i = node->arguments.size() - 1; i >= 0; i--)
    {
        node->arguments[i]->accept(*this);
        //std::cout << "\tmovq " << registerMap[this->allocatedRegister].first << ", " << argumentRegisters[i] << "\n";
    }
    std::cout << "\tmovq $0, %rax\n";
    std::cout << "\tcall " << node->getIdentifier() << "\n";
    std::cout << "\tpopq %r11\n\tpopq %r10\n";
    int r = allocateRegister();
    std::cout << "\tmovq %rax, " << r << "\n";
    this->allocatedRegister = r;
}

void GenTACVisitor::visitProgramNode(ProgramNode* node)
{
    std::cout << ".global main\n";
    std::cout << ".data\n";
    std::cout << ".text\n\n";

    for (const auto& entry : StringSymbolTable::table)
    {
        printLabel(entry.second);
        labelCount++;
        std::cout << "\t.string " << entry.first << "\n";
    }

    for (const auto& programUnit : node->getProgramUnits())
    {
        programUnit->accept(*this);
        freeAllRegisters();
    }
}

void GenTACVisitor::visitWhileNode(WhileNode* node)
{

}

void GenTACVisitor::visitStringLiteralNode(StringLiteralNode* node)
{
    //reg stringRegister = allocateRegister();
    std::cout << "\tmovq $.L" << StringSymbolTable::table[node->value] << ", ";
    // std::cout << registerMap[stringRegister].first << "\n";
    //this->allocatedRegister = stringRegister;
}

int GenTACVisitor::allocateRegister()
{
    return tempCount++;
}

int GenTACVisitor::allocateLabel()
{
    return labelCount++;
}




void GenTACVisitor::visitVariableDeclarationNode(VariableDeclarationNode* node)
{
    // localOffset -= 8;
    // locals.push_back(Local(node->getIdentifier(), scope, localOffset));

    if (node->getRHS())
    {
        node->getRHS()->accept(*this);
        std::cout << node->getIdentifier() << " = " << this->currentName << "\n";
        //std::cout << "\tmovq t" << this->allocatedRegister << "\n";
    }
}

int GenTACVisitor::resolveLocal(std::string identifier)
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

std::string GenTACVisitor::invertInstruction(BinaryOperatorNode* node)
{
    switch (node->op)
    {
        case LessThanOperator:
            return "jge";
        case LessThanOrEqualToOperator:
            return "jg";
        case GreaterThanOperator:
            return "jle";
        case GreaterThanOrEqualToOperator:
            return "jl";
        case EqualsOperator:
            return "jne";
    }
    return "unknown";

}

void GenTACVisitor::visitVariableNode(VariableNode* node)
{
    int offset = resolveLocal(node->getIdentifier());
    this->variableName = node->getIdentifier();
    this->currentName = node->getIdentifier();
    if (!isAssignment)
    {
        loadLocal(offset);
    }
    else
    {

    }
    return;
}


void GenTACVisitor::loadLocal(int offset)
{
    // int store = allocateRegister();
    // // std::cout << "\tmovq " << offset << "(%rbp), " << store << "\n";
    // //std::cout << "t" << store << " = " << this->variableName << "\n";
    // this->allocatedRegister = store;
    // this->currentName = n
}

void GenTACVisitor::printLabel(int label)
{
    std::cout << ".L" << label << ":\n";
}

void GenTACVisitor::freeAllRegisters()
{
    // for (int i = 0; i < registerMap.size(); i++)
    // {
    //     freeRegister(i);
    // }
}

void GenTACVisitor::jumpToLabel(int label)
{
    std::cout << "\tJMP .L" << label << "\n";
}
