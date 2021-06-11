#ifndef VISITOR_H
#define VISITOR_H

class IntNode;
class BinOpNode;
class CompoundStatementNode;
class IfStatementNode;
class PrintNode;
class VariableDeclarationNode;
class BooleanLiteralNode;

class Visitor
{
    public:
    virtual void visitIntNode(IntNode &node) = 0;
    virtual void visitBinOPNode(BinOpNode &node) = 0;
    virtual void visitCompoundStatementNode(CompoundStatementNode &node) = 0;
    virtual void visitIfStatementNode(IfStatementNode &node) = 0;
    virtual void visitPrintNode(PrintNode &node) = 0;
    virtual void visitVariableDeclarationNode(VariableDeclarationNode &node) = 0;
    virtual void visitBooleanLiteralNode(BooleanLiteralNode &node) = 0;


};

#endif