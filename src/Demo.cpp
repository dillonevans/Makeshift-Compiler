#include <iostream>
#include <string>

#include "../headers/AstNode.h"
#include "../headers/Visitor.h"
#include "../headers/BinOpNode.h"
#include "../headers/IntNode.h"

#include "../headers/Parser.h" 
#include "../headers/EmitByteCodeVisitor.h"
#include "../headers/VM.h"
#include "../headers/TypeCheckingVisitor.h"

int main()
{
    EmitByteCodeVisitor v;
    TypeCheckingVisitor typeChecker;
    Parser parser("in.txt");
    parser.printTokens();
    ASTNode* AST = parser.parseCompoundStatement();
    AST->accept(typeChecker);
    
    AST->accept(v);
    VM virtualMachine(v.getInstructions());
    // virtualMachine.dumpByteCode();
    virtualMachine.disassembleInstruction();
    virtualMachine.run();

  
    return 0;
}