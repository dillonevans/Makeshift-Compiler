#ifndef __GENTACVISITOR_H__
#define __GENTACVISITOR_H__


#include "Visitor.h"
#include <unordered_map>
#include <string>
#include <vector>
#include "Local.h"
#include "ThreeAddressCode.h"

class GenTACVisitor : public Visitor
{
private:


    int labelCount = 0, scope = 0, endFunctionLabel = 0, tempCount = 0;
    std::string currentName;
    std::string variableName;
    bool isAssignment = false;
    std::vector<ThreeAddressCode> instructions;
    int allocatedRegister;
    int allocateRegister();
    int allocateLabel();
    void freeAllRegisters();
    void loadLocal(int offset);
    void printLabel(int label);
    void jumpToLabel(int label);
    int resolveLocal(std::string identifier);
    std::vector<Local> locals;
    std::string invertInstruction(BinaryOperatorNode* node);
    int currentLabel = 0;

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

#endif // __GENTACVISITOR_H__