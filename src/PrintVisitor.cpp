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

void PrintVisitor::visitIntegerLiteralNode(IntegerLiteralNode* node)
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
