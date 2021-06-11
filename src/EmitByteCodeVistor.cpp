#include "../headers/BinOpNode.h"
#include "../headers/CompoundStatementNode.h"
#include "../headers/IfStatementNode.h"
#include "../headers/IntNode.h"
#include "../headers/EmitByteCodeVisitor.h"
#include "../headers/VariableDeclarationNode.h"
#include "../headers/BooleanLiteralNode.h"
#include "../headers/Visitor.h"
#include "../headers/PrintNode.h"
#include <iomanip>

void EmitByteCodeVisitor::printInstruction(uint8_t opcode, int constant)
{
    numInstructions++;
}

void EmitByteCodeVisitor::visitBinOPNode(BinOpNode &node)
{
    if (node.left){
        node.left->accept(*this);
    }
    if (node.right){
        node.right->accept(*this);
    }

    switch(node.op)
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

void EmitByteCodeVisitor::visitIntNode(IntNode &node)
{  
    printInstruction(LOAD, node.value);
    instructions.push_back(ByteCodeInstruction(LOAD, node.value));
    return;
}

void EmitByteCodeVisitor::visitCompoundStatementNode(CompoundStatementNode &node)
{
    for (auto statement : node.getStatements())
    {
        statement->accept(*this);
    }
}

void EmitByteCodeVisitor::visitIfStatementNode(IfStatementNode &node)
{
    int falsePointer = 0xff, thenJump = 0, elseJump = 0;
    node.getCondition()->accept(*this);

    //Save the instruction number to modify the jump later
    //If the instructions condition was false, jump ahead to the else clause if any
    thenJump = instructions.size();
    instructions.push_back(ByteCodeInstruction(JF, falsePointer));
    //Otherwise, pop the result of the evaluation and execute the 'then' portion
    instructions.push_back(ByteCodeInstruction(POP));
    node.getIfStmtBody()->accept(*this);
    //Update the first jump instruction
    instructions[thenJump].setConstant(instructions.size() + 1);

    //Store the location of the current jump instruction
    
    //If the condition was true, the VM needs to jump outside of the else clause
    elseJump = instructions.size();
    instructions.push_back(ByteCodeInstruction(JUMP, falsePointer));
    /*If the condition was false, the VM jumps here and executes the else clause so we pop the stack
    to get rid of the result */
    instructions.push_back(ByteCodeInstruction(POP));

    if (node.getElseBody()) {
        node.getElseBody()->accept(*this);
    }
    
    instructions[elseJump].setConstant(instructions.size());
}

std::vector<ByteCodeInstruction> EmitByteCodeVisitor::getInstructions()
{
    return instructions;
}

void EmitByteCodeVisitor::visitPrintNode(PrintNode &node)
{
    node.contents->accept(*this);
    instructions.push_back(PRINT);
}

void EmitByteCodeVisitor::visitVariableDeclarationNode(VariableDeclarationNode &node) {node.rhs->accept(*this);}

void EmitByteCodeVisitor::visitBooleanLiteralNode(BooleanLiteralNode &node) 
{
    instructions.push_back(ByteCodeInstruction(LOAD, node.value));
    return;
}
