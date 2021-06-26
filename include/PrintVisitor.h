#ifndef PRINT_VISITOR_H
#define PRINT_VISITOR_H
#include "Visitor.h"
#include "Type.h"
#include <stack>
#include <string>
class PrintVisitor : public Visitor
{
private:
    int indentation = 0;
    bool isLeft = false;
    void printIndent();

public:
    void visitBinaryOperatorNode(BinaryOperatorNode* node);
    void visitIntegerLiteralNode(IntegerLiteralNode* node);
    void visitCompoundStatementNode(CompoundStatementNode* node);
    void visitIfStatementNode(IfStatementNode* node);
    void visitVariableDeclarationNode(VariableDeclarationNode* node);
    void visitBooleanLiteralNode(BooleanLiteralNode* node);
    void visitVariableNode(VariableNode* node);
    void visitFunctionDeclarationNode(FunctionDeclarationNode* node);
    void visitReturnNode(ReturnNode* node);
    void visitFunctionCallNode(FunctionCallNode* node);
    void visitProgramNode(ProgramNode* node);
    void visitWhileNode(WhileNode* node);
    void visitStringLiteralNode(StringLiteralNode* node);
};

#endif