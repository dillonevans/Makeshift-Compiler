#ifndef VISITOR_H
#define VISITOR_H

class IntegerLiteralNode;
class BinaryOperatorNode;
class CompoundStatementNode;
class IfStatementNode;
class FunctionDeclarationNode;
class VariableDeclarationNode;
class BooleanLiteralNode;
class VariableNode;
class ReturnNode;
class FunctionCallNode;
class ProgramNode;
class WhileNode;
class StringLiteralNode;

class Visitor
{
public:
    virtual void visitIntegerLiteralNode(IntegerLiteralNode* node) = 0;
    virtual void visitBinaryOperatorNode(BinaryOperatorNode* node) = 0;
    virtual void visitCompoundStatementNode(CompoundStatementNode* node) = 0;
    virtual void visitIfStatementNode(IfStatementNode* node) = 0;
    virtual void visitVariableDeclarationNode(VariableDeclarationNode* node) = 0;
    virtual void visitBooleanLiteralNode(BooleanLiteralNode* node) = 0;
    virtual void visitVariableNode(VariableNode* node) = 0;
    virtual void visitFunctionDeclarationNode(FunctionDeclarationNode* node) = 0;
    virtual void visitReturnNode(ReturnNode* node) = 0;
    virtual void visitFunctionCallNode(FunctionCallNode* node) = 0;
    virtual void visitProgramNode(ProgramNode* node) = 0;
    virtual void visitWhileNode(WhileNode* node) = 0;
    virtual void visitStringLiteralNode(StringLiteralNode* node) = 0;
};

#endif