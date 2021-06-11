#include "../headers/BinOpNode.h"
#include "../headers/CompoundStatementNode.h"
#include "../headers/IfStatementNode.h"
#include "../headers/IntNode.h"
#include "../headers/TypeCheckingVisitor.h"
#include "../headers/VariableDeclarationNode.h"
#include "../headers/BooleanLiteralNode.h"
#include "../headers/Visitor.h"
#include "../headers/PrintNode.h"
#include "../headers/Value.h"
#include <iostream>


void TypeCheckingVisitor::visitBinOPNode(BinOpNode &node)
{
    Type t1, t2;
    if (node.left){
        node.left->accept(*this);
        t1 = this->getType();
    }
    if (node.right){
        node.right->accept(*this);
        t2 = this->getType();
    }

    switch(node.op)
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

void TypeCheckingVisitor::visitIntNode(IntNode &node)
{  
    this->setType(IntegerPrimitive);
    return;
}

void TypeCheckingVisitor::visitCompoundStatementNode(CompoundStatementNode &node)
{
    for (auto statement : node.getStatements())
    {
        statement->accept(*this);
    }
    return;
}

void TypeCheckingVisitor::visitIfStatementNode(IfStatementNode &node)
{
    node.getCondition()->accept(*this);
    node.getIfStmtBody()->accept(*this);
    if (node.getElseBody()) {node.getElseBody()->accept(*this);}
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

void TypeCheckingVisitor::visitPrintNode(PrintNode &node)
{
    node.contents->accept(*this);
    return;
}

void TypeCheckingVisitor::visitVariableDeclarationNode(VariableDeclarationNode &node) {node.rhs->accept(*this);}

void TypeCheckingVisitor::visitBooleanLiteralNode(BooleanLiteralNode &node) 
{
    this->setType(BooleanPrimitive);
    return;
}
