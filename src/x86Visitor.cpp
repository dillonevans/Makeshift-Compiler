#include "../headers/x86Visitor.h"


#include "../headers/BinaryOperatorNode.h"
#include "../headers/CompoundStatementNode.h"
#include "../headers/IfStatementNode.h"
#include "../headers/IntegerLiteralNode.h"
#include "../headers/VariableDeclarationNode.h"
#include "../headers/BooleanLiteralNode.h"
#include "../headers/Visitor.h"
#include "../headers/VariableNode.h"
#include "../headers/FunctionDeclarationNode.h"
#include "../headers/ReturnNode.h"
#include "../headers/ProgramNode.h"
#include "../headers/Type.h"
#include "../headers/FunctionCallNode.h"
#include "../headers/StringSymbolTable.h"
#include "../headers/StringLiteralNode.h"
#include <iostream>

void x86Visitor::visitBinaryOperatorNode(BinaryOperatorNode* node)
{
    reg l, r;
    switch (node->op)
    {
        case AdditionOperator:
            node->left->accept(*this);
            l = this->allocatedRegister;
            node->right->accept(*this);
            r = this->allocatedRegister;
            std::cout << "\taddq " << registerMap[l].first << ", " << registerMap[r].first << "\n";
            freeRegister(l);
            this->allocatedRegister = r;
            break;
        case SubtractionOperator:
            node->left->accept(*this);
            l = this->allocatedRegister;
            node->right->accept(*this);
            r = this->allocatedRegister;
            std::cout << "\tsubq " << registerMap[r].first << ", " << registerMap[l].first << "\n";
            freeRegister(r);
            this->allocatedRegister = l;
            break;
        case MultiplicationOperator:
            node->left->accept(*this);
            l = this->allocatedRegister;
            node->right->accept(*this);
            r = this->allocatedRegister;
            std::cout << "\timulq " << registerMap[l].first << ", " << registerMap[r].first << "\n";
            freeRegister(l);
            this->allocatedRegister = r;
            break;
        case AssignmentOperator:
            //Loads the result into the register
            if (node->left)
            {
                node->left->accept(*this);
                l = this->allocatedRegister;

            }
            //This moves the result from the register into the variable's location
            if (node->right)
            {
                isAssignment = true;
                node->right->accept(*this);
                isAssignment = false;
            }
            std::cout << "\tmovq " << registerMap[l].first << ", " << this->variableName << "\n";
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
            std::cout << "\tcmpq " << registerMap[r].first << ", " << registerMap[l].first << "\n";
            std::cout << "\t" << instruction << " .L" << this->currentLabel << "\n";
            freeRegister(r);
            break;
    }
};

void x86Visitor::visitIntegerLiteralNode(IntegerLiteralNode* node)
{
    reg store = allocateRegister();
    std::cout << "\tmovq $" << node->value << ", " << registerMap[store].first << "\t\t# store " << node->value << " in " << registerMap[store].first << "\n";
    this->allocatedRegister = store;
}

void x86Visitor::visitCompoundStatementNode(CompoundStatementNode* node)
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

void x86Visitor::visitIfStatementNode(IfStatementNode* node)
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

void x86Visitor::visitBooleanLiteralNode(BooleanLiteralNode* node)
{

}

void x86Visitor::visitReturnNode(ReturnNode* node)
{
       // std::cout << "END FUNCITON LABEL: " << this->endFunctionLabel << "\n";

    //Generate the code for the return value
    node->toReturn->accept(*this);
    //Move the result into rax
    std::cout << "\tmovq " << registerMap[this->allocatedRegister].first << ", " << "%rax" << "\t\t# store the return value into %rax\n";
    jumpToLabel(this->endFunctionLabel);
}

void x86Visitor::visitFunctionDeclarationNode(FunctionDeclarationNode* node)
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
        std::cout << "\tmovq " << argumentRegisters[index++] << ", " << (localOffset) << "(%rbp)\n";
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
    localOffset = 0;
}

void x86Visitor::visitFunctionCallNode(FunctionCallNode* node)
{
    std::cout << "\tpushq %r10\n\tpushq %r11\n";

    for (int i = node->arguments.size() - 1; i >= 0; i--)
    {
        node->arguments[i]->accept(*this);
        std::cout << "\tmovq " << registerMap[this->allocatedRegister].first << ", " << argumentRegisters[i] << "\n";
    }
    std::cout <<"\tmovq $0, %rax\n";
    std::cout << "\tcall " << node->getIdentifier() << "\n";
    std::cout << "\tpopq %r11\n\tpopq %r10\n";
    int r = allocateRegister();
    std::cout << "\tmovq %rax, " << registerMap[r].first << "\n";
    this->allocatedRegister = r;
}

void x86Visitor::visitProgramNode(ProgramNode* node)
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

void x86Visitor::visitWhileNode(WhileNode* node)
{

}

void x86Visitor::visitStringLiteralNode(StringLiteralNode* node)
{
    reg stringRegister = allocateRegister();
    std::cout << "\tmovq $.L" << StringSymbolTable::table[node->value] << ", ";
    std::cout << registerMap[stringRegister].first << "\n";
    this->allocatedRegister = stringRegister;
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
    std::cout << "OOF";
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
    localOffset -= 8;
    locals.push_back(Local(node->getIdentifier(), scope, localOffset));
    if (node->getRHS())
    {
        node->getRHS()->accept(*this);
        std::cout << "\tmovq " << registerMap[this->allocatedRegister].first << ", " << localOffset << "(%rbp)\n";
        freeRegister(this->allocatedRegister);
    }
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

std::string x86Visitor::invertInstruction(BinaryOperatorNode* node)
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

void x86Visitor::visitVariableNode(VariableNode* node)
{
    int offset = resolveLocal(node->getIdentifier());
    if (!isAssignment)
    {
        loadLocal(offset);
    }
    else
    {
        this->variableName = std::to_string(offset) + "(%rbp)";
    }
    return;
}


void x86Visitor::loadLocal(int offset)
{
    reg store = allocateRegister();
    std::cout << "\tmovq " << offset << "(%rbp), " << registerMap[store].first << "\n";
    this->allocatedRegister = store;
}

void x86Visitor::printLabel(int label)
{
    std::cout << ".L" << label << ":\n";
}

void x86Visitor::freeAllRegisters()
{
    for (int i = 0; i < registerMap.size(); i++)
    {
        freeRegister(i);
    }
}

void x86Visitor::jumpToLabel(int label)
{
    std::cout << "\tJMP .L" << label << "\n";
}
