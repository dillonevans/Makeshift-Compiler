#ifndef EBCV_H
#define EBCV_H
#include "Visitor.h"
#include <vector>
#include <unordered_map>
#include "ByteCodeInstruction.h"
class EmitByteCodeVisitor : public Visitor
{
    private:
    std::vector<ByteCodeInstruction> instructions;
    std::unordered_map<std::string, int> functionAddressMap;

    int labelCount = 0;
    public:
    void visitBinOPNode(BinOpNode &node);
    void visitIntNode(IntNode &node);
    void visitCompoundStatementNode(CompoundStatementNode &node);
    void visitIfStatementNode(IfStatementNode &node);
    void visitPrintNode(PrintNode &node);
    void visitVariableDeclarationNode(VariableDeclarationNode &node);
    void visitBooleanLiteralNode(BooleanLiteralNode &node);
    void visitVariableNode(VariableNode &node);
    void visitFunctionNode(FunctionNode &node);
    void visitReturnNode(ReturnNode &node);
    void visitFunctionCallNode(FunctionCallNode &node);
    void visitProgramNode(ProgramNode &node);

    std::vector<ByteCodeInstruction> getInstructions();
};

#endif