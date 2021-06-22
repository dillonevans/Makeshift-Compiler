#ifndef X86_VISITOR_H
#define X86_VISITOR_H

#include "Visitor.h"
#include <unordered_map>
#include <string>
#include <vector>
#include "Local.h"

using reg = int;
class x86Visitor : public Visitor
{
private:
    std::unordered_map<int, std::pair<std::string, bool>> registerMap
    {
        {0, std::pair<std::string, bool>{"%rbx", false}},
        {1, std::pair<std::string, bool>{"%r10", false}},
        {2, std::pair<std::string, bool>{"%r11", false}},
        {3, std::pair<std::string, bool>{"%r12", false}},
        {4, std::pair<std::string, bool>{"%r13", false}},
        {5, std::pair<std::string, bool>{"%r14", false}},
        {6, std::pair<std::string, bool>{"%r15", false}}
    };
    int labelCount = 0, scope = 0, localOffset = 0;
    int allocateRegister();
    int allocateLabel();
    void freeRegister(int reg);
    bool isAssignment = false;
    std::string variableName;
    int resolveLocal(std::string identifier);
    std::vector<Local> locals;
    reg allocatedRegister;

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

};
#endif 