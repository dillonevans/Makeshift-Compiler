#include "../headers/BinOpnode.h"
#include "../headers/CompoundStatementnode.h"
#include "../headers/IfStatementnode.h"
#include "../headers/Intnode.h"
#include "../headers/PrintVisitor.h"
#include "../headers/VariableDeclarationnode.h"
#include "../headers/BooleanLiteralnode.h"
#include "../headers/Visitor.h"
#include "../headers/Printnode.h"
#include "../headers/Variablenode.h"
#include "../headers/Functionnode.h"
#include "../headers/FunctionCallnode.h"

#include "../headers/Returnnode.h"
#include "../headers/Programnode.h"
#include "../headers/Returnnode.h"

#include "../headers/Value.h"
#include <iostream>
#include <string>


void PrintVisitor::printIndent()
{
    std::cout << std::string(indentation, ' ');
}

void PrintVisitor::visitBinOPNode(BinOpNode* node)
{
    if (!node) { return; }
    indentation++;
    printIndent();
    switch (node->op)
    {
        case AdditionOperator:
            std::cout << "+\n";
            break;
        case SubtractionOperator:
            std::cout << "-\n";
            break;
        case MultiplicationOperator:
            std::cout << "*\n";
            break;
        case DivisionOperator:
            std::cout << "-\n";
            break;

    }
    node->left->accept(*this);
    node->right->accept(*this);
    indentation--;
}

void PrintVisitor::visitIntNode(IntNode* node)
{
    indentation++;
    printIndent();
    std::cout << node->value << "\n";
    indentation--;
}

void PrintVisitor::visitCompoundStatementNode(CompoundStatementNode* node)
{
    for (auto& statement : node->getStatements())
    {
        statement->accept(*this);
    }
}

void PrintVisitor::visitIfStatementNode(IfStatementNode* node)
{

}

void PrintVisitor::visitPrintNode(PrintNode* node)
{
    indentation++;
    printIndent();
    std::cout << "print\n";
    node->contents->accept(*this);
    indentation--;
}

void PrintVisitor::visitVariableDeclarationNode(VariableDeclarationNode* node)
{
    printIndent();
    node->getVarNode()->accept(*this);
    node->getRHS()->accept(*this);
}

void PrintVisitor::visitBooleanLiteralNode(BooleanLiteralNode* node)
{
}

void PrintVisitor::visitVariableNode(VariableNode* node)
{
    indentation++;
    printIndent();
    std::cout << node->getIdentifier() << "\n";
    indentation--;
}

void PrintVisitor::visitFunctionNode(FunctionNode* node)
{
    indentation++;
    printIndent();
    std::cout << node->getFunctionName() << "\n";
    node->getFunctionBody()->accept(*this);
    indentation--;
    return;
}

void PrintVisitor::visitReturnNode(ReturnNode* node)
{
    //node->accept(*this);
}

void PrintVisitor::visitFunctionCallNode(FunctionCallNode* node)
{
    // node->accept(*this);
}

void PrintVisitor::visitProgramNode(ProgramNode* node)
{
    for (auto& programUnit : node->getProgramUnits())
    {
        programUnit->accept(*this);
    }
}

void PrintVisitor::visitWhileNode(WhileNode* node)
{

}