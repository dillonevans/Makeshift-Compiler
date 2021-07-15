#include "../include/BinaryOperatorNode.h"
#include "../include/CompoundStatementnode.h"
#include "../include/IfStatementnode.h"
#include "../include/IntegerLiteralNode.h"
#include "../include/PrintVisitor.h"
#include "../include/VariableDeclarationnode.h"
#include "../include/BooleanLiteralnode.h"
#include "../include/Visitor.h"
#include "../include/Variablenode.h"
#include "../include/FunctionDeclarationNode.h"
#include "../include/FunctionCallnode.h"

#include "../include/Returnnode.h"
#include "../include/Programnode.h"
#include "../include/Returnnode.h"

#include "../include/Type.h"
#include <iostream>
#include <string>


void PrintVisitor::printIndent()
{
    std::cout << std::string(indentation, ' ');
}

void PrintVisitor::visitBinaryOperatorNode(BinaryOperatorNode* node)
{
    if (!node) { return; }

    if (node->op != AssignmentOperator)
    {
        node->left->accept(*this);
    }
    else
    {
        node->right->accept(*this);
    }
    switch (node->op)
    {
        case AdditionOperator:
            std::cout << " + ";
            break;
        case SubtractionOperator:
            std::cout << " - ";
            break;
        case MultiplicationOperator:
            std::cout << " * ";
            break;
        case DivisionOperator:
            std::cout << " - ";
            break;
        case AssignmentOperator:
            std::cout << " = ";
            break;
        case LessThanOrEqualToOperator:
            std::cout << " <= ";
            break;

    }
    if (node->op != AssignmentOperator)
    {
        node->right->accept(*this);
    }
    else
    {
        node->left->accept(*this);
    }

}

void PrintVisitor::visitIntegerLiteralNode(IntegerLiteralNode* node)
{
    std::cout << node->value;
}

void PrintVisitor::visitCompoundStatementNode(CompoundStatementNode* node)
{
    std::cout << "\n";
    printIndent();
    std::cout << "{\n";
    indentation += 4;
    for (auto& statement : node->getStatements())
    {
        printIndent();
        statement->accept(*this);
        std::cout << ";\n";
    }
    indentation -= 4;
    printIndent();
    std::cout << "}\n";

}

void PrintVisitor::visitIfStatementNode(IfStatementNode* node)
{
    std::cout << "if (";
    node->getCondition()->accept(*this);
    std::cout << ")";
    node->getIfStmtBody()->accept(*this);
}

void PrintVisitor::visitVariableDeclarationNode(VariableDeclarationNode* node)
{
    std::cout << "int ";
    node->getVarNode()->accept(*this);
    std::cout << " = ";
    node->getRHS()->accept(*this);
}

void PrintVisitor::visitBooleanLiteralNode(BooleanLiteralNode* node)
{
}

void PrintVisitor::visitVariableNode(VariableNode* node)
{
    std::cout << node->getIdentifier();
}

void PrintVisitor::visitFunctionDeclarationNode(FunctionDeclarationNode* node)
{
    std::cout << "int ";
    std::cout << node->getFunctionName();
    std::cout << "()";
    node->getFunctionBody()->accept(*this);
    return;
}

void PrintVisitor::visitReturnNode(ReturnNode* node)
{
    std::cout << "return ";
    node->toReturn->accept(*this);
}

void PrintVisitor::visitFunctionCallNode(FunctionCallNode* node)
{
    std::cout << node->getIdentifier();
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
