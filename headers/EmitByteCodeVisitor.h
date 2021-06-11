#ifndef EBCV_H
#define EBCV_H
#include "Visitor.h"
#include <vector>
#include "ByteCodeInstruction.h"
class EmitByteCodeVisitor : public Visitor
{
    private:
    std::vector<ByteCodeInstruction> instructions;

    public:
    void visitBinOPNode(BinOpNode &node);
    void visitIntNode(IntNode &node);
    void visitCompoundStatementNode(CompoundStatementNode &node);
    void visitIfStatementNode(IfStatementNode &node);
    void visitPrintNode(PrintNode &node);
    void visitVariableDeclarationNode(VariableDeclarationNode &node);
    void visitBooleanLiteralNode(BooleanLiteralNode &node);
    void visitVariableNode(VariableNode &node);
    std::vector<ByteCodeInstruction> getInstructions();
};

#endif