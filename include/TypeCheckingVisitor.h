#ifndef TCV_H
#define TCV_H
#include "Visitor.h"
#include "Type.h"
class TypeCheckingVisitor : public Visitor
{
private:
    Type type, functionType;
    bool isTypeInference = false;

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
    void setType(Type type);
    void visitStringLiteralNode(StringLiteralNode* node);

    Type getType();
};

#endif