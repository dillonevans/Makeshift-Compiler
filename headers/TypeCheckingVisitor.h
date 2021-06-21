#ifndef TCV_H
#define TCV_H
#include "Visitor.h"
#include "Value.h"
class TypeCheckingVisitor : public Visitor
{
private:
    Type type, functionType;
    bool isTypeInference = false;

public:
    void visitBinOPNode(BinOpNode* node);
    void visitIntNode(IntNode* node);
    void visitCompoundStatementNode(CompoundStatementNode* node);
    void visitIfStatementNode(IfStatementNode* node);
    void visitPrintNode(PrintNode* node);
    void visitVariableDeclarationNode(VariableDeclarationNode* node);
    void visitBooleanLiteralNode(BooleanLiteralNode* node);
    void visitVariableNode(VariableNode* node);
    void visitFunctionNode(FunctionNode* node);
    void visitReturnNode(ReturnNode* node);
    void visitFunctionCallNode(FunctionCallNode* node);
    void visitProgramNode(ProgramNode* node);
    void visitWhileNode(WhileNode* node);
    void visitAssignmentNode(AssignmentNode* node);
    void setType(Type type);

    Type getType();
};

#endif