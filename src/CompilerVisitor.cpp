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
#include "../headers/WhileNode.h"
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
    int falsePointer = 0xff, thenJumpIndex = 0, elseJumpIndex = 0;

    //Generate the Bytecode for the condition of the if statement
    node->getCondition()->accept(*this);

    //Save the instruction number to modify the jump later
    thenJumpIndex = instructions.size();

    //If the instructions condition was false, jump ahead to the else clause if any
    instructions.push_back(ByteCodeInstruction(JF, falsePointer));

    //Otherwise, pop the result of the evaluation and execute the 'then' portion
    instructions.push_back(ByteCodeInstruction(POP));
    node->getIfStmtBody()->accept(*this);

    //Update the first jump instruction
    instructions[thenJumpIndex].setConstant(instructions.size() + 1);

    //If the condition was true, the VM needs to jump outside of the else clause
    elseJumpIndex = instructions.size();
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
    instructions[elseJumpIndex].setConstant(instructions.size());
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
    locals.push_back(Local(node->getIdentifier(), scope));
    node->getRHS()->accept(*this);
}

int CompilerVisitor::resolveLocal(std::string identifier)
{
    for (int i = locals.size() - 1; i >= 0; i--)
    {
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
    scope++;
    instructions.push_back(ByteCodeInstruction(LABEL, labelCount++));
    functionAddressMap[node->getFunctionName()] = instructions.size() - 1;

    /**
     * Add every parameter to the local array so that they can be accessed
     * relative to their stack location
     */
    for (const auto& parameter : node->getParameterList())
    {
        locals.push_back(Local(parameter->getIdentifier(), scope));
    }

    //Generate the Bytecode for the body of the function
    node->getFunctionBody()->accept(*this);

    //After the function ends, pop all of the local variables off the stack and decrement scope
    while (locals.size() > 0)
    {
        instructions.push_back(ByteCodeInstruction(POP));
        locals.pop_back();
    }
    scope--;

    //After the function ends, return. 
    instructions.push_back(ByteCodeInstruction(RETURN));
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

void CompilerVisitor::visitWhileNode(WhileNode* node)
{
    int falsePointer = 0xff, beginWhileIndex = 0, endWhileIndex = 0;

    //Save the instruction number to modify the jump later
    beginWhileIndex = instructions.size();

    //This is the start of the while loop
    instructions.push_back(ByteCodeInstruction(LABEL, labelCount++));

    //Generate Bytecode for the condition
    node->getCondition()->accept(*this);

    //If the condition was false, jump to the end of the while loop
    endWhileIndex = instructions.size();
    instructions.push_back(ByteCodeInstruction(JF, falsePointer));

    //Generate Bytecode for the body
    node->getBody()->accept(*this);
    instructions.push_back(ByteCodeInstruction(JUMP, beginWhileIndex));

    /**
     * This label marks the end of the while loop. When the while
     * condition is false, the instruction pointer is moved here
     * and the stack is popped, for it contains the result of the
     * condition.
     */
    instructions[endWhileIndex].setConstant(instructions.size());
    instructions.push_back(ByteCodeInstruction(LABEL, labelCount++));
    instructions.push_back(ByteCodeInstruction(POP));
}
