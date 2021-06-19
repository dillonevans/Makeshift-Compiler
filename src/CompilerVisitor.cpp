#include "../headers/BinOpNode.h"
#include "../headers/CompoundStatementNode.h"
#include "../headers/IfStatementNode.h"
#include "../headers/IntNode.h"
#include "../headers/CompilerVisitor.h"
#include "../headers/VariableDeclarationNode.h"
#include "../headers/BooleanLiteralNode.h"
#include "../headers/Visitor.h"
#include "../headers/PrintNode.h"
#include "../headers/VariableNode.h"
#include "../headers/FunctionNode.h"
#include "../headers/FunctionCallNode.h"
#include "../headers/ReturnNode.h"
#include "../headers/ProgramNode.h"
#include "../headers/Local.h"
#include <iomanip>
#include <iostream>

void CompilerVisitor::visitBinOPNode(BinOpNode* node)
{
    if (!node) { return; }
    if (node->left) { node->left->accept(*this); }
    if (node->right) { node->right->accept(*this); }

    switch (node->op)
    {
        case AdditionOperator:
            instructions.push_back(ByteCodeInstruction(ADD));
            break;
        case MultiplicationOperator:
            instructions.push_back(ByteCodeInstruction(MULT));
            break;
        case DivisionOperator:
            instructions.push_back(ByteCodeInstruction(DIV));
            break;
        case SubtractionOperator:
            instructions.push_back(ByteCodeInstruction(SUB));
            break;
        case LessThanOperator:
            instructions.push_back(ByteCodeInstruction(LT));
            break;
        case GreaterThanOperator:
            instructions.push_back(ByteCodeInstruction(GT));
            break;
        case LogicalAndOperator:
            instructions.push_back(ByteCodeInstruction(AND));
            break;
        case LogicalOrOperator:
            instructions.push_back(ByteCodeInstruction(OR));
            break;
    }
    return;
};

void CompilerVisitor::visitIntNode(IntNode* node)
{
    instructions.push_back(ByteCodeInstruction(LOAD, node->value));
    return;
}

void CompilerVisitor::visitCompoundStatementNode(CompoundStatementNode* node)
{
    scope++;
    for (auto& statement : node->getStatements())
    {
        statement->accept(*this);
    }
    scope--;
    while (locals.size() > 0 && locals.back().getScope() > scope)
    {
        locals.pop_back();
        instructions.push_back(ByteCodeInstruction(POP));
    }
}

void CompilerVisitor::visitIfStatementNode(IfStatementNode* node)
{
    int falsePointer = 0xff, thenJump = 0, elseJump = 0;

    //Generate the Bytecode for the condition of the if statement
    node->getCondition()->accept(*this);

    //Save the instruction number to modify the jump later
    thenJump = instructions.size();

    //If the instructions condition was false, jump ahead to the else clause if any
    instructions.push_back(ByteCodeInstruction(JF, falsePointer));

    //Otherwise, pop the result of the evaluation and execute the 'then' portion
    instructions.push_back(ByteCodeInstruction(POP));
    node->getIfStmtBody()->accept(*this);

    //Update the first jump instruction
    instructions[thenJump].setConstant(instructions.size() + 1);

    //If the condition was true, the VM needs to jump outside of the else clause
    elseJump = instructions.size();
    instructions.push_back(ByteCodeInstruction(JUMP, falsePointer));

    /*If the condition was false, the VM jumps here and executes the else clause so we pop the stack
    to get rid of the result */
    instructions.push_back(ByteCodeInstruction(LABEL, labelCount++));
    instructions.push_back(ByteCodeInstruction(POP));

    //If there is an else body, we generate the code for it
    if (node->getElseBody())
    {
        node->getElseBody()->accept(*this);
    }

    /**
     * Regardless if there is an else statement, we jump to the end of the if
     */
    instructions[elseJump].setConstant(instructions.size());
    instructions.push_back(ByteCodeInstruction(LABEL, labelCount++));
}

std::vector<ByteCodeInstruction> CompilerVisitor::getInstructions()
{
    return instructions;
}

void CompilerVisitor::visitPrintNode(PrintNode* node)
{
    node->contents->accept(*this);
    instructions.push_back(PRINT);
}

void CompilerVisitor::visitVariableDeclarationNode(VariableDeclarationNode* node)
{
    std::cout << "identifier:" << node->getIdentifier() << "\n";
    locals.push_back(Local(node->getIdentifier(), scope));
    node->getRHS()->accept(*this);
}

int CompilerVisitor::resolveLocal(std::string identifier)
{
    std::cout << "Locals Size: " << locals.size() << "\n";
    for (int i = locals.size() - 1; i >= 0; i--)
    {
        std::cout << "Identifier: " << locals[i].getIdentifier() << "\n";
        if (identifier == locals[i].getIdentifier())
        {
            return i;
        }
    }
    return -1;
}

void CompilerVisitor::visitVariableNode(VariableNode* node)
{
    int arg = resolveLocal(node->getIdentifier());
    std::cout << arg << "\n";
    instructions.push_back(ByteCodeInstruction(LOAD_LOCAL, arg));
    return;
}

void CompilerVisitor::visitBooleanLiteralNode(BooleanLiteralNode* node)
{
    instructions.push_back(ByteCodeInstruction(LOAD, node->value));
    return;
}

void CompilerVisitor::visitReturnNode(ReturnNode* node)
{

    return;
}

void CompilerVisitor::visitFunctionNode(FunctionNode* node)
{
    instructions.push_back(ByteCodeInstruction(LABEL, labelCount++));
    scope++;
    std::cout << node->getFunctionName() << "\n";
    functionAddressMap[node->getFunctionName()] = instructions.size() - 1;
    for (const auto& parameter : node->getParameterList())
    {
        locals.push_back(Local(parameter->getIdentifier(), scope));
    }
    node->getFunctionBody()->accept(*this);
    while (locals.size() > 0)
    {
        instructions.push_back(ByteCodeInstruction(POP));
        locals.pop_back();
    }
    instructions.push_back(ByteCodeInstruction(RETURN));
    scope--;
    return;
}

void CompilerVisitor::visitFunctionCallNode(FunctionCallNode* node)
{
    //Push the return address onto the stack as well as the function call
    instructions.push_back(ByteCodeInstruction(LOAD, instructions.size() + 1));
    instructions.push_back(ByteCodeInstruction(CALL, functionAddressMap[node->getIdentifier()]));
}

void CompilerVisitor::visitProgramNode(ProgramNode* node)
{

    //This makes the call to main, the address gets recalculated afterwards
    instructions.push_back(ByteCodeInstruction(LOAD, 0xff));
    instructions.push_back(ByteCodeInstruction(CALL, 0xff));
    for (auto& programUnit : node->getProgramUnits())
    {
        programUnit->accept(*this);
    }
    //After the bytecode instructions have been generated, update the address of main
    instructions[1].setConstant(functionAddressMap["main"]);
}
