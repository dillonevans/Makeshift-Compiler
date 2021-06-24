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

#include "../headers/Type.h"
#include <iostream>
#include <string>


void PrintVisitor::printIndent()
{
    std::cout << std::string(indentation, ' ');
}

void PrintVisitor::visitBinOPNode(BinOpNode* node)
{
    if (!node) { return; }
    indentation += 4;
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
        case AssignmentOperator:
            std::cout << "=\n";

    }
    node->left->accept(*this);
    node->right->accept(*this);
    indentation -= 4;
}

void PrintVisitor::visitIntNode(IntNode* node)
{
    std::cout << node->value;
}

void PrintVisitor::visitCompoundStatementNode(CompoundStatementNode* node)
{
    indentation += 4;
    std::cout << "{\n";
    for (auto& statement : node->getStatements())
    {
        printIndent();
        statement->accept(*this);
        std::cout << ";\n";
    }
    std::cout << "}\n";
    indentation -= 4;

}

void PrintVisitor::visitIfStatementNode(IfStatementNode* node)
{

}

void PrintVisitor::visitPrintNode(PrintNode* node)
{

    std::cout << "print\n";
    node->contents->accept(*this);
}

void PrintVisitor::visitVariableDeclarationNode(VariableDeclarationNode* node)
{
    std::cout << "int ";
    node->getVarNode()->accept(*this);
    std::cout << "= ";
    node->getRHS()->accept(*this);
}

void PrintVisitor::visitBooleanLiteralNode(BooleanLiteralNode* node)
{
}

void PrintVisitor::visitVariableNode(VariableNode* node)
{
    std::cout << node->getIdentifier() << " ";
}

void PrintVisitor::visitFunctionNode(FunctionNode* node)
{
    std::cout << "int ";
    std::cout << node->getFunctionName();
    std::cout << "()";
    node->getFunctionBody()->accept(*this);
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
    for (const auto& programUnit : node->getProgramUnits())
    {
        programUnit->accept(*this);
    }
}

void PrintVisitor::visitWhileNode(WhileNode* node)
{

}

void PrintVisitor::visitStringLiteralNode(StringLiteralNode* node)
{

}
