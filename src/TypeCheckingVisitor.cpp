#include "../headers/BinOpNode.h"
#include "../headers/CompoundStatementNode.h"
#include "../headers/IfStatementNode.h"
#include "../headers/IntNode.h"
#include "../headers/TypeCheckingVisitor.h"
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

void TypeCheckingVisitor::visitBinOPNode(BinOpNode* node)
{
    Type t1, t2;
    if (node->left) {
        node->left->accept(*this);
        t1 = this->getType();
    }
    if (node->right) {
        node->right->accept(*this);
        t2 = this->getType();
    }

    switch (node->op)
    {
        case AdditionOperator:
        case SubtractionOperator:
        case DivisionOperator:
        case MultiplicationOperator:
            if (t1 == BooleanPrimitive || t2 == BooleanPrimitive)
            {
                std::cout << "Invalid operand types";
                exit(EXIT_FAILURE);
            }
            if (t1 == IntegerPrimitive)
            {
                if (t2 == t1)
                {
                    this->setType(IntegerPrimitive);
                }
            }
            break;
        case GreaterThanOperator:
        case LessThanOperator:
            if (t1 == BooleanPrimitive || t2 == BooleanPrimitive)
            {
                std::cout << "Invalid operand types";
                exit(EXIT_FAILURE);
            }
            this->setType(BooleanPrimitive);
            break;
        case LogicalAndOperator:
        case LogicalOrOperator:
            if (t1 != BooleanPrimitive || t2 != BooleanPrimitive)
            {
                std::cout << "Invalid operand types";
                exit(EXIT_FAILURE);
            }
            this->setType(BooleanPrimitive);
            break;
    }
    return;

};

void TypeCheckingVisitor::visitIntNode(IntNode* node)
{
    this->setType(IntegerPrimitive);
    return;
}

void TypeCheckingVisitor::visitCompoundStatementNode(CompoundStatementNode* node)
{
    for (auto statement : node->getStatements())
    {
        statement->accept(*this);
    }
    return;
}

void TypeCheckingVisitor::visitIfStatementNode(IfStatementNode* node)
{
    node->getCondition()->accept(*this);
    node->getIfStmtBody()->accept(*this);
    if (node->getElseBody()) { node->getElseBody()->accept(*this); }
    return;
}

void TypeCheckingVisitor::setType(Type type)
{
    this->type = type;
}

Type TypeCheckingVisitor::getType()
{
    return this->type;
}

void TypeCheckingVisitor::visitPrintNode(PrintNode* node)
{
    node->contents->accept(*this);
    return;
}

void TypeCheckingVisitor::visitVariableNode(VariableNode* node)
{
    if (isTypeInference)
    {
        node->setType(type);
    }
    else
    {
        this->setType(node->getType());
    }
    return;
}

void TypeCheckingVisitor::visitVariableDeclarationNode(VariableDeclarationNode* node)
{
    Type t1, t2;
    node->getVarNode()->accept(*this);
    t1 = this->getType();
    node->getRHS()->accept(*this);
    t2 = this->getType();
    if (t1 == ImplicitVarType)
    {
        isTypeInference = true;
        type = t2;
        node->getVarNode()->accept(*this);
        this->setType(t2);
        isTypeInference = false;
    }
    else if (t1 == IntegerPrimitive)
    {
        if (t2 == BooleanPrimitive)
        {
            std::cerr << "Cannot initialize type int with type boolean";
            exit(EXIT_FAILURE);
        }
        this->setType(t1);
    }
    else if (t1 == BooleanPrimitive)
    {
        if (t2 == IntegerPrimitive)
        {
            std::cerr << "Cannot initialize type bool with type int";
            exit(EXIT_FAILURE);
        }
        this->setType(BooleanPrimitive);
    }
}

void TypeCheckingVisitor::visitBooleanLiteralNode(BooleanLiteralNode* node)
{
    this->setType(BooleanPrimitive);
    return;
}

void TypeCheckingVisitor::visitReturnNode(ReturnNode* node)
{
    node->toReturn->accept(*this);
    Type returnType = this->getType();
    if (returnType != functionType)
    {
        std::cerr << "Function must return specified type\n";
    }
    return;
}

void TypeCheckingVisitor::visitFunctionNode(FunctionNode* node)
{
    functionType = node->getReturnType();
    node->getFunctionBody()->accept(*this);
    return;
}

void TypeCheckingVisitor::visitFunctionCallNode(FunctionCallNode* node)
{

}

void TypeCheckingVisitor::visitProgramNode(ProgramNode* node)
{
    for (auto& programUnit : node->getProgramUnits())
    {
        programUnit->accept(*this);
    }
}

void TypeCheckingVisitor::visitWhileNode(WhileNode* node)
{

}
